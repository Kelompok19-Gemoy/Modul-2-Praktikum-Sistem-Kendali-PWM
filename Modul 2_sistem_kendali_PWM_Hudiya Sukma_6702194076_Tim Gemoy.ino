//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Modul Praktikum 2 - Sistem Kendali PWM
// Nama Tim : Gemoy
// Nama Anggota 1 : Nadia Novemi Wilza
// Nama Anggota 2 : Hudiya Sukma
// Versi Program : 1.0

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Deklarasi Variabel Sensor
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//Variable motor
int pinEnable = 4; //Harus diset HIGH apabila akan diaktifkan
int pinEnable2 = 2; //Harus diset HIGH apabila akan diaktifkan

//Motor kiri
int motor_kiri1 = 5; //Input motor driver 1 L293D
int motor_kiri2 = 6; //Input motor driver 2 L293D

//Motor kanan
int motor_kanan1 = 3; //Input motor driver 3 L293D
int motor_kanan2 = 11; //Input motor driver 3 L293D

//Variable bantuan
int x;
int LastError;

void setup()
{
  //pinmode input sensor
  pinMode(sensor1, INPUT); //Set pin A0 sebagai input
  pinMode(sensor2, INPUT); //Set pin A1 sebagai input
  pinMode(sensor3, INPUT); //Set pin A2 sebagai input
  pinMode(sensor4, INPUT); //Set pin A3 sebagai input
  pinMode(sensor5, INPUT); //Set pin A4 sebagai input
  pinMode(sensor6, INPUT); //Set pin A5 sebagai input
   
  //pinmode output sensor
  pinMode(pinEnable, OUTPUT);
  pinMode(pinEnable2, OUTPUT);
  pinMode(motor_kiri1, OUTPUT);
  pinMode(motor_kiri2, OUTPUT);
  pinMode(motor_kanan1, OUTPUT);
  pinMode(motor_kanan2, OUTPUT);
  
  //Inisialisasi komunikasi serial
  Serial.begin(9600); //Baud standar 9600
}

void readsensor() { // untuk membaca sensor kemudian menyimpan Array
  baca_sensor[0] = analogRead(sensor1);
  baca_sensor[1] = analogRead(sensor2);
  baca_sensor[2] = analogRead(sensor3);
  baca_sensor[3] = analogRead(sensor4);
  baca_sensor[4] = analogRead(sensor5);
  baca_sensor[5] = analogRead(sensor6);
  
  delay(1000);
  //Menampilkan data sensor ke Serial Monitor
  //Data Sensor 1-6
  //Formatting tampilan data sensor
  for (x=0; x<=5; x++){
    Serial.print("Sensor ");
    Serial.print(x+1);
    Serial.print(" : ");
    Serial.println(baca_sensor[x]);
    Serial.print(" ");
    Serial.print("\n");
  }
}

void loop(){
  //nilai terendah photodiode = 33(paling gelap)
  //nilai tertinggi photodiode = 687(paling terang)
    
    readsensor();
	Serial.print("Nilai Last Error : ");//
  
  //Sensor 1 dan 2 mendeteksi gelap --> Duty cycle 0% motor kiri, 50% motor kanan
    if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
      
      //Duty cycle motor kiri 0%
      	digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
      //Duty cycle motor kanan 50%
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
     
    }
  //Sensor 2 dan 3 mendeteksi gelap, sisanya terang --> Duty cycle 20% motor kiri, 50% motor kanan
    else if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
             baca_sensor[2] < 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
      	
      //Duty cycle motor kiri 20%
        digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0.2*255);
        analogWrite(motor_kiri2, 0);
        
      //Duty cycle motor kanan 50%
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 127);
        analogWrite(motor_kanan2, 0);
      Serial.print("Error = -1 ");
      LastError = -1;
    }
  
  //Sensor 3 dan 4 mendeteksi gelap, sisanya terang --> Duty cycle 60% pada kedua motor
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
      	
      //Duty cycle motor kiri 60%
        digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0.6*255);
        analogWrite(motor_kiri2, 0);
        
      //Duty cycle motor kanan 60%
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.6*255);
        analogWrite(motor_kanan2, 0); 
    }
  
  //Sensor 4 dan 5 mendeteksi gelap, sisanya terang --> Duty cycle 50% motor kiri, 20% motor kanan 
    else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] < 34 && 
             baca_sensor[4] < 34 && baca_sensor[5] > 34){
      	
      //Duty cycle motor kiri 50%
        digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
      //Duty cycle motor kanan 20%
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.2*255);
        analogWrite(motor_kanan2, 0);
    }
  
  //Sensor 5 dan 6 mendeteksi gelap, sisanya terang --> Duty cycle 50% Motor kiri, 0% motor kanan
  	else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] < 34 && baca_sensor[5] < 34){
      	
      //Duty cycle motor kiri 50%
        digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
      //Duty cycle motor kanan 0%
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0);
        analogWrite(motor_kanan2, 0);
    }
  
  //Semua sensor mendeteksi terang --> Semua sensor mendeteksi terang
  	else if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
             baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
             baca_sensor[4] > 34 && baca_sensor[5] > 34){
      	
        digitalWrite(pinEnable, HIGH);
      //analogWrite(pin, value 0-255)
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0);
        analogWrite(motor_kanan2, 0);
    }
  //Error Detection Memory
  //Studi kasus 2 : Error Condition --> hanya 1 buah sensor terbaca
  //Simpan kondisi terakhir pada suatu variable
  //Ketika Sensor 1 saja yang mendeteksi gelap
  
  //Sensor 1 saja yang mendeteksi gelap
  	 if (baca_sensor[0] < 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        //Error = -2
       //Eksekusi kasus Sensor 1 dan 2
      	digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.5*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = -2");
       LastError = -2;
    }
  
  	//Sensor 2 saja yang mendeteksi gelap
  	 if (baca_sensor[0] > 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        //Error = -1
       //Eksekusi kasus Sensor 2 dan 3
      	digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.2*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.5*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = -1");
       LastError = -1;
    }
  
  	//Sensor 3 atau 4 saja yang mendeteksi gelap
  	 if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] < 34 || baca_sensor[3] < 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34){
     
        //Error = 0
       //Eksekusi kasus Sensor 3 dan 4
      	digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.6*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.6*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 0");
       LastError = 0;
    }
  
  	//Sensor 5 saja yang mendeteksi gelap
  	 if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] > 34){
     
       //Error = 1
       //Eksekusi kasus Sensor 4 dan 5
      	digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0.2*255);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 1");
       LastError = 1;
    }
  
  //Sensor 6 saja yang mendeteksi gelap
  	 if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] < 34){
        
       //Error = 2
       //Eksekusi kasus Sensor 5 dan 6
      	digitalWrite(pinEnable, HIGH);
        analogWrite(motor_kiri1, 0.5*255);
        analogWrite(motor_kiri2, 0);
        
        digitalWrite(pinEnable2, HIGH);
        analogWrite(motor_kanan1, 0);
        analogWrite(motor_kanan2, 0);
       Serial.print("Error = 2");
       LastError = 2;
    }
  
  else{}
}