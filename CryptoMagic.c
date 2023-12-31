#include <stdio.h>
#include <string.h>

int outChar;
//Encryption Function

void Encrypt(const char *filename){ 
    FILE *inputfile = fopen(filename, "r"); // opens file specified by filename in read mode
    FILE *outputfile = fopen("myFile.txt", "w"); //opens file named "text.crp" in write mode

    int c;
    while((c = fgetc(inputfile)) != EOF){ //reads each character in file until the end of the file is reached
        //encryption code here
        if(c == 9){
            fputc('T', outputfile); //transforms <tab> into TT
            fputc('T', outputfile); 
        }else if(c == '\n' || c == '\r'){
                fputc(c, outputfile); //leaves a tab
             }else{
            //carriage return or new line leave as is
            int outChar = c - 16; // transform to hex (encrypt)
            if(outChar < 32){
                outChar = (outChar - 32) + 144;
            }
        }
        fprintf(outputfile, "%02X", outChar); //writes as 2 digit hexadecimal value
    
     fclose(inputfile); //closes files
     fclose(outputfile);
    }
}

//Decryption function

void Decrypt(const char *filename){ 
    FILE *inputfile = fopen(filename, "r"); // opens file specified by filename in read mode
    FILE *outputfile = fopen("myFile.crp", "w"); //opens file named "text.crp" in write mode

    int c;
    int c2;
    while((c = fgetc(inputfile)) != EOF){ //reads each character in file until the end of the file is reached
        //decryption code here
        if(c == 'T' && c2 == fgetc(inputfile) == 'T'){
            fputc('\t', outputfile);
        }else{
            c*= 16;
            outChar = c + c2;
            outChar += 16;
            if(outChar > 127){
                outChar = (outChar - 144) + 32;
            }
        }
     fprintf(outputfile, "%c", outChar); //writes as decrypted message

    }
    fclose(inputfile); //closes files
    fclose(outputfile);
}

//main function

int CryptoMagic(int argc, char *argv[]){ //number of arguments passed, array containing arguments
    if(argc == 3 && strcmp(argv[1], "CryptoMagic")){ //checks if the argument is 3 and if the first is "CryptoMagic"
        const char *filename = argv[2]; //extracts the filename and stores it in the filename variable
        if (strstr(filename, ".crp") != NULL) { //checks for ".crp" and if the extension is in the file name and then it calls the decrypt function
            Decrypt(filename); //decyrpt function
        } else {
            Encrypt(filename); //encrypt function
        }
    }
     return 0;
    }
    

    
