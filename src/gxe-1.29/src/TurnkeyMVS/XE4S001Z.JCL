//AWSREAD  JOB REGION=8192K,MSGCLASS=A                                  00010001
//CPY EXEC PGM=IEBCOPY                                                  00080001
//SYSPRINT DD SYSOUT=*                                                  00090001
//SYSUT3  DD UNIT=SYSDA,SPACE=(TRK,(10))                                00100001
//SYSUT4  DD UNIT=SYSDA,SPACE=(TRK,(10))                                00110001
//DD1     DD DISP=OLD,UNIT=(TAPE,,DEFER),VOL=SER=VOLSER,                00120001
//        LABEL=(1,SL),DSN=AWSDATA                                      00121001
//DD2     DD DISP=OLD,DSN=SAK01.LOAD.TMP     <== SPECIFY TARGET LIBRARY 00130001
//SYSIN   DD *                                                          00140001
  COPY OUTDD=DD2,INDD=DD1                                               00150001
