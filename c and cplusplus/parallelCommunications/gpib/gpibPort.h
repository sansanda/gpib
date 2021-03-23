#ifndef GPIBPORT_H
#define GPIBPORT_H

#include "./gpib/parallelCommunications/parallelport.h"
//#include "./Instruments/keithley/sourceMeters/K24xxConfigurationParameters.h"
//#include "./instruments/keithley2410.h"
#include "./debugTools/debug.h"
#include "./models/ValidInstrumentsParameters.h"
#include "./debugTools/debug.h"

#include <QMessageBox>

#define BOARD_INDEX 0
#define SAD 0
#define READ_SIZE 100

#define TIMEOUT_1s T1s
#define TIMEOUT_3s T3s
#define TIMEOUT_10s T10s
#define TIMEOUT_30s T30s
#define TIMEOUT_100s T100s
#define NEVERTIMEOUT TNONE

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
        #include "./gpib/Adgpib.h"
        #include "./gpib/gpib_user.h"
    #endif
#endif

class GPIBPort: public ParallelPort{

    Q_OBJECT
public:

    GPIBPort();
    GPIBPort(int addr);
    ~GPIBPort();

    void     closeConnection();
    void     disable();
    int      openConnection(int eos = 0 );
    int      checkPresence();
    int      write( QString instruction);
    int      write( char *instruction );
    int      read (int size, QVariant &result);
    int      read( char * message, int size );
    int      sendReadQueryAndGetResultAsCharArray( char* message, int bytesToRead );
    int      sendReadQueryAndGetResultAsString(int size, QString &result);
    int      remoteEnable();
    void     clearDevice();
    bool     isNoError();
    void     setNoError(bool state);

    int      setTimeout (int timo);
    void     setAddress(int addr);
    int      getAddress();

    int      testInstrunction(QString instruction);
    int      allResgistersQueryTest();

    int      stbQuery();
    QString  sreQuery();
    QVariant eseQuery();
    QVariant esrQuery();
    QVariant oerQuery();
    QVariant merQuery();
    QVariant qerQuery();

    void readQueryAsCharArray(char* message, const int size);

    int getDevice() const;
    void setDevice(int value);

private:
    int     address;
    bool    noError = true;
    int     device;

protected:
    int      errors();
    void     errorMessage( QString errorType );

signals:
    void     errorSignal();


};

#endif // GPIBPORT_H
