//*CID://+v911R~:                              update#=   16;      //~v911R~
//***********************************************************      //~v90gI~
//* xp2p.h                                                         //~v90gR~
//***********************************************************      //~v90gI~
//020718 v911 form2p support(ex a42,b4l2). /y2 max col is of a4,b4l2 max col is of b5//~v911I~
//010527 v90k :2 page support for also not unx version             //~v90gI~
//010521 v90g :LINUX support:double pageing                        //~v90gI~
//**********************************************************************//~v90gI~
//****************************************************************************//~v90gI~
int putline2p(char *Pbuff,int Phdrcmdlen,unsigned long Plen,FILE *Pfh);//~v90kR~
//****************************************************************************//~v90gI~
void closedoc2p(void);                                             //~v90kR~
//**********************************************************************//~v90gI~
int get2pwidth(int Pprintwidth);                                   //+v911I~