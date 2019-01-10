/**

 * @file gpib.cpp
 * @author  Luis Rodriguez <luis.rodriguez@csic.es>
 * @version 0.1
 *
 * @brief basic GPIB functions
 * @section DESCRIPTION
 *
 * The GPIB class implements the basic gpib functions using the driver instructions.
 * Open, write, read and close. This is design as a basic class to be inherits for all the
 * devices classes.
 *
 */

#include "../GPIB/gpib.h"

/**
  * @brief Read messages from GPIB bus.
  *
  * @return A char[100] that contains 42 bytes read from the device.
  */

static bool noError = true;
static int device;




QVariant Gpib::read(const int size)
{
#ifndef TEST
    char measure[size + 50];
    if( noError ){
        read( measure, size);
        errors();
    }

    return QVariant(measure);
#else
    return QVariant("+9.979305E-01,+1.003080E-04,+1.074219E-02\n");
    //return QVariant("UM, RANGE=12.000kV, VALUE=1.053kV");
    //return QVariant("+5.000000E+00,+8.249011E-05,+5.285156E+02,+6.111000E+00,+8.381449E-05,+5.285205E+02,+7.222000E+00,+8.429056E-05,+5.285254E+02,+8.333500E+00,+8.415909E-05,+5.285303E+02,+9.444500E+00,+8.352670E-05,+5.285352E+02,+1.055550E+01,+8.389394E-05,+5.285400E+02,+1.166650E+01,+8.381329E-05,+5.285449E+02,+1.277800E+01,+8.840705E-05,+5.285498E+02,+1.388900E+01,+8.393636E-05,+5.285547E+02,+1.500000E+01,+8.438555E-05,+5.285596E+02\n\320\231\210\001\210a"" @0x1528be8");
#endif

}


/**
  * @brief Read the device GPIB message.
  *
  * @param message Is the storage buffer for the read data.
  * @param size An integer that specifies the maximum number of bytes to read.
  */
void Gpib::read(char * message, int size){
#ifndef TEST
    if( noError ){
        ibrd (device, message, size);
        errors();
    }
#endif
}

/**
  * @brief check the presence of a device in the bus.
  *
  * @param pad An integer that represents de primary address for the device to open.
  */

int Gpib::checkPresence(){
    int status = EXIT_SUCCESS;

#ifndef TEST
    QString output = QString( "*IDN?" );

    if( Gpib::isNoError() )
    {
        Gpib::write( output.toLocal8Bit().data());
    }
    status = errors();
    Gpib::read(200);
    status = errors();
#endif
    return status;
}


/**
  * @brief Open a device GPIB connection.
  *
  * @param pad An integer that represents de primary address for the device to open.
  */

int Gpib::open(int pad, int eos){
    int status = EXIT_SUCCESS;
#ifndef TEST
    short listen;

    if( noError ){
        int v;
        std::cout<<"Looking for the GPIB Interface"<<std::endl;
        ibask(BOARD_INDEX,1,&v);
        status = errors();
    }
    if( noError ){
        std::cout<<"****************************************************************************"<<device<<std::endl;
        device = ibdev(BOARD_INDEX, pad, SAD, TIMEOUT, EOT, eos);
        //std::cout<<"****************************************************************************"<<device<<std::endl;
        status = errors();
    }
    if( noError ){
        ibln( 0, pad, SAD, &listen);
        //std::cout<<"****************************************************************************"<<a<<std::endl;
        status = errors();
    }
#endif
    setNoError(true);
    return status;
}

/**
  * @brief Write a desired GPIB instruction.
  *
  * @param instruction A char sequence that contains the GPIB instruction desired.
  */
void Gpib::write(char * instruction){
#ifndef TEST
    if( noError){
        ibwrt( device, instruction, strlen(instruction) );
        errors();
    }
#endif
}

/**
  * @brief Asserts/unasserts remote enableazaa
  */
void Gpib::remoteEnable()
{
#ifndef TEST
    if( noError ){
        //ibsre( device, 1 ); // depracated
        ibconfig( device, IbcSRE, 1);
        errors();
    }
#endif
}

/**
  * @brief Clear a specific device
  */
void Gpib::clear()
{
#ifndef TEST
    if( noError){
        ibclr( device );
        errors();
    }
#endif
}

/**
  * @brief go local
  */

void Gpib::close(){
#ifndef TEST
    // Force the device into local mode
    if( noError ){
        ibloc( device );
        errors(); // Just check for errors if there is no previous errors
        // avoids errors loops
    }
#endif
}

/**
  * @brief Close device
  */

void Gpib::disable(){
#ifndef TEST
    // Force the device into local mode
    if( noError ){
        ibonl(device, 0);
        errors();
    }
#endif
}

bool Gpib::isNoError() {return noError;}

void Gpib::setNoError(bool state) {noError = state;}

/**
  * @brief Detect if a GPIB error just happened.
  */

int Gpib::errors(){
    int status = EXIT_SUCCESS;
#ifndef TEST

    if( ( ibsta & ERR ) == ERR ) {
        //We have and error!
        //Extracting type of error
        QString errorMessageText = "GPIB Error: ";
        switch( iberr ){
        case EDVR:
            errorMessageText.append("System error.");
            status = -1;break;
        case ECIC:
            errorMessageText.append("Function requires GPIB board to be CIC.");
            status = -1;break;
        case ENOL:
            errorMessageText.append("Write function detected no Listeners.");
            status = -2;break;
        case EADR:
            errorMessageText.append("Interface board not addressed correctly.");
            status = -1;break;
        case EARG:
            errorMessageText.append("Invalid argument to function call.");
            status = -1;break;
        case ESAC:
            errorMessageText.append("Function requires GPIB board to be SAC.");
            status = -1;break;
        case EABO:
            errorMessageText.append("I/O operation aborted.");
            status = -1;break;
        case ENEB:
            errorMessageText.append("Non-existent interface board.");
            status = -1;break;
        case EDMA:
            errorMessageText.append("DMA hardware error detected.");
            status = -1;break;
        case EOIP:
            errorMessageText.append("I/O operation started before previous operation completed.");
            status = -1;break;
        case ECAP:
            errorMessageText.append("No capability for intended operation.");
            status = -1;break;
        case EFSO:
            errorMessageText.append("File system operation error.");
            status = -1;break;
        case EBUS:
            errorMessageText.append("Command error during device call.");
            status = -1;break;
        case ESTB:
            errorMessageText.append("Serial poll status byte lost.");
            status = -1;break;
        case ESRQ:
            errorMessageText.append("SRQ remains asserted.");
            status = -1;break;
        case ETAB:
            errorMessageText.append("The return buffer is full.");
            status = -1;break;
        }
        errorMessage( errorMessageText );
    }
#endif
    return status;
}

/**
  * @brief Pop up errors
  *
  * @param erroType A QString that holds the error type.
  */

void Gpib::errorMessage(QString errorType)
{
    //QMessageBox errorBox;
    //errorBox.setIcon( QMessageBox::Critical );

    std::cout<<errorType.toLocal8Bit().constData()<<std::endl;

    //errorBox.setText( errorType.toLocal8Bit().constData());
    //errorBox.exec();
    setNoError(false);
    //emit errorSignal();
}
