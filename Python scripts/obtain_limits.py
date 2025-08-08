import yarp
import re
import time

def get_joint_limits_rpc(remote_rpc_port, num_joints):
    port = yarp.Port()
    port.open("/client/limits/rpc:o")

    if not yarp.Network.connect("/client/limits/rpc:o", remote_rpc_port):
        print(f"No se pudo conectar al puerto RPC remoto: {remote_rpc_port}")
        port.close()
        return None

    limits = {}

    for j in range(num_joints):
        cmd = f"get llim {j}"
        bottle = yarp.Bottle()
        bottle.fromString(cmd)

        response = yarp.Bottle()
        success = port.write(bottle, response)

        if not success:
            print(f"Error enviando comando para joint {j} en {remote_rpc_port}")
            continue

        text = response.toString()
        m = re.search(r'llim\s(-?\d+\.?\d*)\s(-?\d+\.?\d*)', text)
        if m:
            min_lim = float(m.group(1))
            max_lim = float(m.group(2))
            limits[j] = (min_lim, max_lim)
        else:
            print(f"No se pudo parsear límite para joint {j} en respuesta: {text}")

        time.sleep(0.05)

    port.close()
    return limits

def main():
    yarp.Network.init()

    parts = {
        "leftArm": "/teoSim/leftArm/rpc:i",
        "rightArm": "/teoSim/rightArm/rpc:i",
        "head": "/teoSim/head/rpc:i",
        "trunk": "/teoSim/trunk/rpc:i",
        "leftLeg": "/teoSim/leftLeg/rpc:i",
        "rightLeg": "/teoSim/rightLeg/rpc:i"
    }

    num_joints_per_part = {
        "leftArm": 6,
        "rightArm": 6,
        "head": 3,
        "trunk": 3,
        "leftLeg": 6,
        "rightLeg": 6
    }

    all_limits = {}

    for part, rpc_port in parts.items():
        print(f"\nObteniendo límites de {part}...")
        limits = get_joint_limits_rpc(rpc_port, num_joints_per_part[part])
        if limits is not None:
            all_limits[part] = limits
            for joint, (mn, mx) in limits.items():
                print(f"{part} joint {joint}: min={mn:.2f}, max={mx:.2f}")
        else:
            print(f"Error obteniendo límites de {part}")

    yarp.Network.fini()

    # Aquí puedes devolver o guardar 'all_limits' como quieras
    return all_limits

if __name__ == "__main__":
    all_limits = main()
