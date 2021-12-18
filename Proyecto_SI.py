# Referencia https://youtu.be/C-jkO6coJkk 

import pyotp
import qrcode
import matplotlib.pyplot as plt
import serial
import time
import threading

class Usuario():
    def __init__(self, nombre: str):
        self.nombre = nombre
        self.__existencia = False
        self.__generar_llave_secreta() # PARA INICIALIZAR EL QR Y USUARIO055
        
    def autenticar(self, contrasena):        
        thread1 = threading.Thread(target = self.__generar_llave_secreta, args = () )
        thread1.daemon = True
        thread1.start()
        if contrasena == self.__generar_llave_secreta():            
            return True
        else:
            return False
        

    def __generar_llave_secreta(self):
        existencia = self.__consultar_usuario()
        
        if existencia == "No encontrado":
            key = pyotp.random_base32()  # -> generamos llave secreta aleatoria para un usuario
            archivo = "RegistroUSUARIOS_" + self.nombre + ".txt"
            registro= {
                "NOMBRE": self.nombre,
                "KEY" : key
                }
            with open(archivo, 'a') as f:
                f.write(str(registro) + str("\n"))
                f.write(str(key))
        else:
            key = str(existencia)
            # key = base64.b32encode(bytearray(key, 'ascii')).decode('utf-8')
            #print("ESTA ES KEY:", key)

        ## CONTRASEÑA Y QR        
        t = pyotp.TOTP(key)  # -> genereamos el objeto TOTP one-tyme password
        nombre_usuario = "UAM@"+ self.nombre
        ## Generar QR        
        auth_str= t.provisioning_uri(name = nombre_usuario, issuer_name = 'UAM-AZC') # generando one time password
        if self.__existencia == False:
            img=qrcode.make(auth_str)            
            img.save(self.nombre + "_UAM.png")

        # -> genereamos el one-tyme password
        contrasena = t.now()            
        # print("Valor: ", t.now())                
        return contrasena    

    def __consultar_usuario(self):
        try: 
            archivo = "RegistroUSUARIOS_" + self.nombre + ".txt"
            cont = 0
            existe = False
            with open(archivo, 'r') as buscar:
                for line in buscar:
                    if self.nombre in line:                    
                        existe = True
                    if existe == True  and cont == 1:
                        self.__existencia = True
                        return line
                    cont +=1
        except: 
            return "No encontrado"

def autenticacion():
    usuario = input("Ingrese el nombre de usuario: ")
    contra = input("Ingrese Codigo de la aplicacion: ")
    identificado = False
    for objeto in user:
        if objeto.nombre == usuario:  
            if objeto.autenticar(contra) == True:
                print(f"BIENVENIDO AL SISTEMA: {objeto.nombre}")
                identificado = True
                arduino.write(b'9')
                break
    if identificado == False:
        arduino.write(b'8')
        print("REVISAR CREDENCIALES")

def espacios():
    print("*********\t*********\t*********\t*********\t*********")
    print("*********\t*********\t*********\t*********\t*********")
    print("*********\t*********\t*********\t*********\t*********")


#### ****************   MAIN    ***********************
print("*********\t*********\t*********\t*********\t*********")
print("\tSISTEMA DE AUTENTICACION DE DOBLE FACTOR")
print("UTILIZACION DE GOOGLE AUTENTICATOR & ARDUINO CON RFID")
print("*********\t*********\t*********\t*********\t*********")
#### USUARIOS ALMACENADOS
alex = Usuario("Alejandro")
ana = Usuario("Ana")
user = [alex, ana]
        
try:
    arduino = serial.Serial('COM5', 9600)
    while True:
        print("[+] INGRESE SU TARJETA RFID")        
        dato_recibido = arduino.readline()        
        if dato_recibido == b'REGISTRADO\r\n':            
            autenticacion()
            
        else:
            print("REVISAR CREDENCIALES")
            
            espacios()
        time.sleep(3)
        espacios()
        
except:
    arduino.close()


