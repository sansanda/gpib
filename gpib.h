#ifndef GPIB_H
#define GPIB_H

#define BOARD_INDEX 0
#define SAD 0
#define READ_SIZE 100
#define TIMEOUT T1s
#define EOT 1

#define FORMAT_DATA_SIZE    14 * 3
/**
  * End Of String
  *  - 0 = none EOS
  *  - 0x140A = {0A} retorno de carro
  */
#define EOS 0

#ifndef TEST
    #ifdef  NI_PCI_GPIB
        #include <windows.h>
        #include "gpib/ni488.h"
    #elif   AD_GPIB
        #include "../GPIB/Adgpib.h"
        #include "../GPIB/gpib_user.h"
    #endif
#endif

#include <QString>
#include <QObject>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include "iostream"


//Low level GPIB-driver communication class
class Gpib:public QObject
{
    Q_OBJECT

public:

    static void close();
    static void disable();
    static int open( int pad, int eos = 0 );
    static int checkPresence();
    static void write( char *instruction );
    static QVariant read(const int size = 42 );
    static void read( char * message, int size );
    static void remoteEnable();
    static void clear();
    static bool isNoError();
    static void setNoError(bool state);


private:

protected:
    static int errors();
    static void errorMessage( QString errorType );

signals:
    void errorSignal();
};


#endif // GPIB_H
