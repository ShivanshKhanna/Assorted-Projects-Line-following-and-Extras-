#include <SPI.h> //include Serial Peripheral Interface library
#include <MFRC522.h> //include MFRC522 library for reader

#define SDA 10  //SS, CS pin controls the sending of data between the master and slave
#define RST 9  //Reset Pin, required for restarting RFID and powering down this object
MFRC522 mfrc522(SDA, RST);  //Create MFRC522 reader object * required for reader and card communication as well as communication between master and slave
MFRC522::MIFARE_Key key; //create a MIFARE microchip Key struct named 'key', this will hold card information, this is a structure required for storing different components into one specific data type (Thompson, 2022).

void setup() {
        Serial.begin(9600);      //Begin serial monitor to display data elements for writing and reading data
        SPI.begin();              //Begin SPI communication protocol, involvement of master - slave communication
        mfrc522.PCD_Init();       // initialize and allocate memory for scanned card towards PCD or proximity coupling device which is also known as an RFID reader
        Serial.println("Scan Card"); //Print to serial monitor and string value for the next print on the next line
        
        //By using code tutorials from Make code, Last Minute Engineers, the card's unique identification or key is required to be stored in row 1 block 0, thus this will be stored 4 bytes, which will already be written in the card

//A security key has to be developed in order for reading and writing functions, where 6 bytes of data will be allocated for storing this key * this will be allocated to 7 individual blocks across different bytes, where these will be set to 0xFF also known as the integer value 255 from the Hexi-decimal number ff (Stack Overflow, 2011)
 
for (byte i = 0; i < 6; i++) {
key.keyByte[i] = 0xFF;//storage of security key across several bytes of data

//keyByte is defined as the MIFARE key structure from the library
        }
}

int block=4; //1st block of the 4th byte, I will write to the MIFARE Card and read it through the serial monitor

byte blockcontent[16] = {"FRBLFRBLFRBL"};  //an array with 16 bytes to be written into one of the 64 card blocks is defined
// This is converted into hexadecimal values allowing for 6 byte storage

//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; //Used for deletion of a block sector, required for replacement of specific block

byte readbackblock[18]; //Array used for reading out a specific block. The MIFARE Read method requires a temporary data storage for input speed and output speed, this is required for holding at least 18 byte to hold the 16 bytes of a block, where it can be read in a sequence (Bolton, 2019).

void loop()
{
 proximity integrated circuit card //Search and check for MIFARE microchip card in proximity
	if ( ! mfrc522.PICC_IsNewCardPresent()) {

// if the PICC for a new card being detected also known as proximity integrated circuit card is true (represented by a 1 or true statement) the rest of the code will be executed, however with a false reading the reader will check again for a new card in proximity
	}

if ( ! mfrc522.PICC_ReadCardSerial()) {
		return; //If a false value occurs (0) return and check for new card.

//This will not work will older cards as I require a intergraded security key, where without it I will not be able to write or read

//Last line of code stores UID or unique identification, required for reading the card
	}
         
        // the PICC_ReadCardSerial() method reads the UID and the SAK (Select acknowledge) into the mfrc522.uid structure, which is combined into a specific data type ready for reading
 
        // The UID number is required for authentication, allowing the card to be read or written
		//byte		size;			// Recognizes size of UID stored in block 0 row 0
		//byte		uidByte[10];    //storage of user ID in 10 bytes.
		//byte		sak;			// The SAK (Select acknowledge) byte returned from the PICC after successful selection.
	        //} Uid; //Required for cleared authentication
         
         Serial.println("card selected");
//Card selected and sent to serial monitor and the string prefix creates a new line

int writeBlock(int blockNumber, byte arrayAddress[]) 
{
//As we can only write to data blocks not trailer blocks (every 4th block containing security), this code below has been configured for prevention of writing over a trailer block
  
int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3; //Determines trailer block where it declares that it should not write over every 4th block
  if (blockNumber > 2 && (blockNumber+1)%4 == 0){Serial.print(blockNumber);Serial.println(" is a trailer block:");return 2;}

//if block number is a trailer block (modulo 4); the if loop will fail sending code error 2
  Serial.print(blockNumber);
  Serial.println(" is a data block:");
  
 byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);

//Required for authentication of a certain block, which will be used for writing or reading
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF, this means that a structure is required for every block, needed as every manufactured card as rows dedicated to 0 X FF 
  //Uid *uid is required as a pointer, containing the user ID in the form of a UID structure, inputted on the card
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
        
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);//valueBlockA is the block number, MIFARE_Write(block number (0-15), byte array containing 16 values, number of bytes in block (=16))
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  Serial.println("block was written");

//Print that the block was written from program to card
}


int readBlock(int blockNumber, byte arrayAddress[]) 
{
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);
  //this method is used to authenticate a certain block for writing or reading
  //command: See enumerations above -> PICC_CMD_MF_AUTH_KEY_A	= 0x60 (=1100000),		// this command performs authentication with Key A
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF
  //Uid *uid is a pointer to the UID struct that contains the user ID of the card.
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
//authentication is required before reading or writing, this will be initiated in every sector

byte buffersize = 18; //Variable definition for read buffer size, where the MIFARE read method requires a pointer to the variable containing its size
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.println("block was read");

//Block is outlined to be reader by serial monitor
}
         
         writeBlock(block, blockcontent); content carried by block content is written onto card
         //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
         
 //The Card has to be placed onto the reader for 6 seconds both for reading and sending to the serial monitor, where the cards information will be dumped when read
       
         
         readBlock(block, readbackblock); //read block content stored on card
         Serial.print("read block: ");
         for (int j=0 ; j<16 ; j++) This will print the contents of the card, involving the specific message
         {
           Serial.write (readbackblock[j]);//Serial.write() Conversion of Hexadecimal/ASCII numbers to readable human characters transmits the ASCII numbers as human readable characters further printed to serial monitor
         }
         Serial.println("");
         
 
}

