# main_combined.py
import serial
import re
import time
import threading
from joint_control import JointController

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 115200
SEND_INTERVAL = 0.2  # Envío de encoders cada 200 ms

# Expresión para mensajes tipo <nombre:indice:valor>
pattern = r"<([a-zA-Z]+):(\d+):([-+]?\d*\.\d+|\d+)>"

def send_encoders(ser, jc):
    while True:
        for part in jc.parts:
            enc = jc.encoders.get(part)
            if not enc:
                continue
            num_joints = enc.getAxes()
            positions = jc.yarp.Vector(num_joints)

            if enc.getEncoders(positions.data()):
                for i in range(num_joints):
                    comando = f"<{part}:{i}:{positions[i]:.2f}>\n"
                    ser.write(comando.encode())
                    ser.flush()
                    print(f"[📤] Enviado a placa: {comando.strip()}")
                    time.sleep(0.005)
            else:
                print(f"[⚠️] Error leyendo encoders de {part}")

        time.sleep(SEND_INTERVAL)

def receive_commands(ser, jc):
    while True:
        try:
            raw_line = ser.readline()
            line = raw_line.decode('utf-8', errors='ignore').strip()

            if line:
                print(f"[📥] Recibido de placa: {line}")
                match = re.match(pattern, line)
                if match:
                    part = match.group(1)
                    index = int(match.group(2))
                    position = float(match.group(3))

                    success = jc.move_joint(part, index, position)
                    if success:
                        print(f"[✅] Movido: {part} [{index}] → {position}")
                        ser.write(b"True\n")
                    else:
                        print(f"[❌] No se pudo mover {part}")
                        ser.write(b"False\n")
                else:
                    print("[⚠️] Formato no válido.")
        except Exception as e:
            print(f"[⚠️] Error en lectura: {e}")
            time.sleep(0.1)

def main():
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        time.sleep(2)
        print(f"[✅] Puerto serie abierto: {SERIAL_PORT}")
    except serial.SerialException as e:
        print(f"[❌] No se pudo abrir el puerto serie: {e}")
        return

    jc = JointController()

    try:
        t_enc = threading.Thread(target=send_encoders, args=(ser, jc), daemon=True)
        t_enc.start()

        receive_commands(ser, jc)

    except KeyboardInterrupt:
        print("[🛑] Interrumpido por el usuario.")
    finally:
        ser.close()
        jc.close()
        print("[🔚] Recursos cerrados.")

if __name__ == "__main__":
    main()
