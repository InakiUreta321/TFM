# joint_control.py
import yarp

class JointController:
    def __init__(self):
        yarp.Network.init()
        self.yarp = yarp
        self.parts = {
            "leftArm": "/teoSim/leftArm",
            "rightArm": "/teoSim/rightArm",
            "head": "/teoSim/head",
            "trunk": "/teoSim/trunk",
            "leftLeg": "/teoSim/leftLeg",
            "rightLeg": "/teoSim/rightLeg"
        }

        self.drivers = {}
        self.encoders = {}
        self.position_controls = {}

        for name, remote in self.parts.items():
            options = yarp.Property()
            options.put("device", "remote_controlboard")
            options.put("remote", remote)
            options.put("local", f"/client/{name}")

            driver = yarp.PolyDriver(options)
            if not driver.isValid():
                print(f"[❌] No se pudo conectar a {name}")
                continue

            enc = driver.viewIEncoders()
            pos = driver.viewIPositionControl()

            if enc and pos:
                self.drivers[name] = driver
                self.encoders[name] = enc
                self.position_controls[name] = pos
                print(f"[✅] Conectado a {name}")
            else:
                print(f"[⚠️] Fallo al obtener interfaces de {name}")
                driver.close()

    def move_joint(self, part, index, position):
        if part in self.position_controls:
            posCtrl = self.position_controls[part]
            posCtrl.positionMove(index, position)
            return True
        return False

    def close(self):
        for driver in self.drivers.values():
            driver.close()
        yarp.Network.fini()
