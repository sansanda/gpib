/**

 * @file scpi.cpp
 * @author  Luis Rodriguez <luis.rodriguez@csic.es>
 * @version 0.1
 *
 * @brief GPIB standard instructions
 * @section DESCRIPTION
 *
 * The SCPI class implements the need standard GPIB instructions. That arent specific for a device,
 * those following Standard Commands for Programmable Instruments format (SCPI).
 *
 */

#include "../GPIB/scpi.h"
#include "./instruments/keithley/sourceMeters/K24xxConfigurationParameters.h"

/**
  * @brief Constructor
  */
Scpi::Scpi()
{
}

Scpi::~Scpi()
{
}

void Scpi::write(QString _message){
    qDebug() << _message.toLocal8Bit().data();
    if(Gpib::isNoError()){
        Gpib::write( _message.toLocal8Bit().data() );
    }
}

/**
 * @brief Reset the device. Restore GPIB defaults values.
 */
void Scpi::reset()
{
    QString output = "*RST";
    qDebug() << output.toLocal8Bit().data();

    if(Gpib::isNoError()){
        Gpib::write( output.toLocal8Bit().data() );
    }
}

/**
 * @brief Voltage source mode.
 */
void Scpi::setInVoltageSourceMode()
{
    QString output = ":SOUR:FUNC VOLT";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Current source mode.
 */
void Scpi::setInCurrentSourceMode()
{
    QString output = ":SOUR:FUNC CURR";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Fixed Voltage source mode.
 */
void Scpi::setInFixedVoltageSourceMode()
{
    QString output = ":SOUR:VOLT:MODE FIXED";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Fixed Current source mode.
 */
void Scpi::setInFixedCurrentSourceMode()
{
    QString output = ":SOUR:CURR:MODE FIXED";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Voltage measure mode.
 */
void Scpi::setInVoltageMeasureMode()
{
    QString output = ":SENS:FUNC 'VOLT'";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Current source mode.
 */
void Scpi::setInCurrentMeasureMode()
{
    QString output = ":SENS:FUNC 'CURR:DC'";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Voltage source range selection.
 *
 * @param voltageSourceRange Is a double containing the voltage source Range value.
 */
void Scpi::setVoltageSourceRange(double voltageSourceRange)
{
    QString output = QString(":SOUR:VOLT:RANG %1").arg(voltageSourceRange);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Current source range selection.
 *
 * @param currentSourceRange Is a double containing the current source Range value.
 */
void Scpi::setCurrentSourceRange(double currentSourceRange)
{
    QString output = QString(":SOUR:CURR:RANG %1").arg(currentSourceRange);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Current source range to min.
 *
 */
void Scpi::setCurrentSourceRangeToMin()
{
    QString output = QString(":SOUR:CURR:RANG MIN");
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}


/**
 * @brief Enable or disable concurrent meausures.
 *
 * @param satus Is a bool that enables (TRUE) or disables (FALSE) concurrent measures.
 */
void Scpi::concurrentMeasure( bool status )
{
    QString output;
    if( status )
        output = ":SENS:FUNC:CONC ON";
    else
        output = ":SENS:FUNC:CONC OFF";

    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set current sense compliance.
  *
  * @param currentCompliance Is a double that contains the limit corrent for the desired measure.
  */

void Scpi::setCurrentCompliance(double currentCompliance)
{
    QString output = QString(":SENS:CURR:PROT %1").arg( currentCompliance );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write(output.toLocal8Bit().data());
}

/**
  * @brief Set voltage sense compliance.
  *
  * @param voltageCompliance Is a double that contains the voltage limit for the desired measure.
  */

void Scpi::setVoltageCompliance(double voltageCompliance)
{
    QString output = QString(":SENS:VOLT:PROT %1").arg( voltageCompliance );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write(output.toLocal8Bit().data());
}

/**
  * @brief Set integration time.
  *
  * @param nplc A QString that holds the nplc value retrieved from the UI.
  */

void Scpi::setNplc(QString nplc)
{
    /* ...VOLT:NPLC is used as instruction for any kind of measure.
    (Keithley Manual) Note that this is a global command. Thus, if you set the speed
    for voltage measurements to 10 PLC, then current and resistance will also set to
    10 PLC.*/
    QString output = ":SENS:VOLT:NPLC " + nplc;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write(output.toLocal8Bit().data());
}

/**
  * @brief Disable or enable auto voltage range.
  *
  * @param status Is a bool that contains wether or not enable or disable auto voltage range.
  */

void Scpi::setVoltageMeasureRangeInAuto(bool status)
{
    QString output;
    if( status )
        output = ":SENS:VOLT:RANG:AUTO ON";
    else
        output = ":SENS:VOLT:RANG:AUTO OFF";

    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set voltage measure range.
  *
  * @param
  */

void Scpi::setVoltageMeasureRange(double measureRange)
{
    QString output = QString(":SENS:VOLT:RANG %1").arg( measureRange );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write(output.toLocal8Bit().data());
}

/**
  * @brief Disable or enable auto current range.
  *
  * @param status Is a bool that contains wether or not enable or disable auto current range.
  */

void Scpi::setCurrentMeasureRangeInAuto(bool status)
{
    QString output;
    if( status )
        output = ":SENS:CURR:RANG:AUTO ON";
    else
        output = ":SENS:CURR:RANG:AUTO OFF";

    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set current measure range.
  *
  * @param measureRange
  */

void Scpi::setCurrentMeasureRange(double measureRange)
{
    QString output = QString(":SENS:CURR:RANG %1").arg( measureRange );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write(output.toLocal8Bit().data());
}

/**
  * @brief Disable or enable filter
  *
  * @param status Is a bool that contains wether or not enable the filter
  */
void Scpi::enableFilter(bool status)
{
    QString output;
    if( status )
        output = ":SENS:AVER:STAT ON";
    else
        output = ":SENS:AVER:STAT OFF";

    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set filter count.
  *
  * @param filterCount A int that holds the number of filter counts.
  */

void Scpi::setFilterCount(int filterCount)
{
    QString output;
    output = QString(":SENS:AVER:COUN %1").arg( filterCount ) ;
    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set filter type.
  *
  * @param filterTypeIndex A int that contains an index that differences from different filter
  * types: EXPonetial, NORMal, REPeat, MOVing.
  */

void Scpi::setFilterType(int filterTypeIndex)
{
    QString output;
    switch ( filterTypeIndex ) {
    case NORMAL_FILTER:
        output = QString(":SENS:AVER:TCON NORM");
        break;
    case REPEAT_FILTER:
        output = QString(":SENS:AVER:TCON REP");
        break;
    case MOVING_FILTER:
        output = QString(":SENS:AVER:TCON MOV");
        break;
    case EXPONENTIAL_FILTER:
        output = QString(":SENS:AVER:TCON EXO");
        break;
    default:
        output = QString(":SENS:AVER:TCON NORM");
        break;
    }
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set voltage source level.
  *
  * @param sourceLevel A double that contains the desired voltage source level for the instrument.
  */

void Scpi::setVoltageSourceLevel(double sourceLevel)
{
    QString output;
    output = QString( ":SOUR:VOLT:LEV %1" ).arg( sourceLevel ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set current source level.
  *
  * @param sourceLevel A double that contains the desired current (in Amps) source level for the instrument.
  */

void Scpi::setCurrentSourceLevel(double sourceLevel)
{
    QString output;
    output = QString( ":SOUR:CURR:LEV %1" ).arg( sourceLevel ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set pulse width.
  *
  * @param sourceLevel A double that contains the pulse width from 0.15ms to 5ms.
  */

void Scpi::setPulseWidth(double width)
{
    QString output;
    output = QString( ":SOUR:PULS:WIDT %1" ).arg( width ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set pulse width.
  *
  * @param sourceLevel A double that contains the pulse width from 0.15ms to 5ms.
  */

void Scpi::setPulseDelay( double pulseDelay )
{
    QString output;
    output = QString( ":SOUR:PULS:DEL %1" ).arg( pulseDelay ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Enable or disable the instrument output.
  *
  * @param output A boolean that holds wether or not to turn off or on the instrument output.
  */

void Scpi::enableOutput(bool status)
{
    QString output;
    if( status )
        output = ":OUTP:STAT ON";
    else
        output = ":OUTP:STAT OFF";

    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}


/**
  * @brief gets the IDN of the instrument.
  */

QVariant Scpi::idnQuery( const int size )
{
    QString output = QString( "*IDN?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
    {
        Gpib::write( output.toLocal8Bit().data());
    }
    return Gpib::read(size);
}

/**
  * @brief Trigger and adquires readings.
  */

QVariant Scpi::readQuery( const int size )
{
    QString output = QString( ":READ?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read( size );
}

/**
  * @brief get data from instrument buffer.
  */

QVariant Scpi::dataQuery( const int size )
{
    QString output = QString( ":TRAC:DATA?" );
    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read( size );
}

/**
  * @brief Fetch data from instrument buffer.
  */

QVariant Scpi::fetchQuery( const int size )
{
    QString output = QString( ":FETC?" );
    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read( size );
}

/**
  * @brief Sends :INIT command to trigger the device measure.
  */

void Scpi::initTrigger()
{
    QString output = QString( ":INIT");
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}


/**
  * @brief Enable measure functions.
  *
  * @param parameters A QString that includes all the functions to enable.
  */

void Scpi::enableMeasureFunctionsSCPI( const QString parameters )
{
    QString output = QString( ":SENS:FUNC:ON " + parameters );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Disables or enables text messages for displays.
  *
  * @param window A int used to choose between top and bottom display.
  * @param state A bool to turn On or Off the display text messages mode.
  */

void Scpi::displayTextState( const int window, bool state )
{
    QString output;
    switch ( window ) {
    case TOP_WINDOW:
        output = QString(":DISP:WIND:TEXT:STAT ");
        break;
    case BOTTOM_WINDOW:
        output = QString(":DISP:WIND2:TEXT:STAT ");
        break;
    default:
        output = QString(":DISP:WIND:TEXT:STAT ");
        break;
    }

    if(state)
        output = output + "ON";
    else
        output = output + "OFF";

    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Display custom texts.
  *
  * @param window A int used to choose between top and bottom display.
  * @param parameters A QString that includes the text to display.
  */

void Scpi::displayText( const int window, const QString text )
{
    QString output;
    switch ( window ) {
    case TOP_WINDOW:
        output = QString(":DISP:WIND:TEXT:DATA \"" + text + "\"");
        break;
    case BOTTOM_WINDOW:
        output = QString(":DISP:WIND2:TEXT:DATA \"" + text + "\"");
        break;
    default:
        output = QString(":DISP:WIND:TEXT:DATA \"" + text + "\"");
        break;
    }

    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );

}

/**
  * @brief Set trigger count.
  *
  * @param triggerCount A integer holding the number of trigger counts betwee 1 to 2500.
  */
void Scpi::setTriggerCount( int triggerCount )
{
    QString output;

    // Avoiding overcome the maximum count trigger.
    if( triggerCount > 2500 )
        triggerCount = 2500;

    output = QString( ":TRIG:COUN %1" ).arg( triggerCount ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep voltage starting point.
  *
  * @param sweepVoltageStart A double holding the sweep voltage starting value.
  */
void Scpi::setVoltageSweepStart(const double sweepVoltageStart)
{
    QString output;

    output = QString( ":SOUR:VOLT:STAR %1" ).arg( sweepVoltageStart ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep voltage stoping point.
  *
  * @param sweepVoltageStart A double holding the sweep voltage stoping value.
  */
void Scpi::setVoltageSweepStop(const double sweepVoltageStop)
{
    QString output;

    output = QString( ":SOUR:VOLT:STOP %1" ).arg( sweepVoltageStop ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep current starting point.
  *
  * @param sweepCurrentStart A double holding the sweep current starting value.
  */
void Scpi::setCurrentSweepStart(const double sweepCurrentStart)
{
    QString output;

    output = QString( ":SOUR:CURR:STAR %1" ).arg( sweepCurrentStart ) ;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep current stoping point.
  *
  * @param sweepCurrentStop A double holding the sweep current stoping value.
  */
void Scpi::setCurrentSweepStop(const double sweepCurrentStop)
{
    QString output;

    output = QString( ":SOUR:CURR:STOP %1" ).arg( sweepCurrentStop );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep voltage step value.
  *
  * @param sweepVoltageStep A double holding the sweep voltage step value.
  */
void Scpi::setVoltageSweepStep(const double sweepVoltageStep)
{
    QString output;

    output = QString( ":SOUR:VOLT:STEP %1" ).arg( sweepVoltageStep );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep current step value.
  *
  * @param sweepCurrentStep A double holding the sweep current step value.
  */
void Scpi::setCurrentSweepStep(const double sweepCurrentStep)
{
    QString output;

    output = QString( ":SOUR:CURR:STEP %1" ).arg( sweepCurrentStep );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set voltage sweep mode.
  */
void Scpi::setVoltageSweepMode()
{
    QString output = ":SOUR:VOLT:MODE SWE";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set current sweep mode.
  */
void Scpi::setCurrentSweepMode()
{
    QString output = ":SOUR:CURR:MODE SWE";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set sweep mode.
  *
  * @param sweepMode An int that holds weather the sweep is linear or logarithmic.
  */
void Scpi::setSweepType(const int sweepType)
{
    QString output;
    switch ( sweepType ) {
    case LINEAR:
        output = QString(":SOUR:SWE:SPAC LIN");
        break;
    case LOG:
        output = QString(":SOUR:SWE:SPAC LOG");
        break;
    default:
        output = QString(":SOUR:SWE:SPAC LIN");
        break;
    }
    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Set the number of sweep points.
  *
  * @param setSweepPoints An int that holds the number of points for a sweep.
  */
void Scpi::setSweepPoints(const int sweepPoints)
{
    QString output;

    output = QString( ":SOUR:SWE:POIN %1" ).arg( sweepPoints );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
  * @brief Test GPIB instructions
  *
  */
void Scpi::testInstrunction(const char *instruction)
{
    QString output = instruction;
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}


/**
 * @brief Clear Status. Clears all event registers and Error Queue.
 */

void Scpi::clearStatus()
{
    QString output = "*CLS";
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program Service Request enable register
 *
 * @param config An int that holds the configuration value for SRE.
 */

void Scpi::programSrqr(const int config)
{
    QString output = QString("*SRE %1").arg(config);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program the Standard Event Enable Register
 *
 * @param config An int that holds the configuration value for Standard Event Enable Register.
 */

void Scpi::programSer(const int config)
{
    QString output = QString("*ESE %1").arg(config);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program the Operation Enable Register
 *
 * @param config An int that holds the configuration value for Operation Enable Register.
 */

void Scpi::programOer(const int config)
{
    QString output = QString(":STAT:OPER:ENAB %1").arg(config);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program the Measurement Enable Register
 *
 * @param config An int that holds the configuration value for Measurement Enable Register.
 */

void Scpi::programMer(const int config)
{
    QString output = QString(":STAT:MEAS:ENAB %1").arg(config);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program the Questionable Enable Register
 *
 * @param config An int that holds the configuration value for Questionable Enable Register.
 */

void Scpi::programQer(const int config)
{
    QString output = QString(":STAT:QUES:ENAB %1").arg(config);
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Select status register format
 *
 * @param format An int used as an index to choose between formats: ASCii, HEXadecimal, OCTal, BINary
 */

void Scpi::formatStatusRegister(const int format)
{
    QString output;
    switch ( format ) {
    case ASCii:
        output = QString(":FORM:SREG ASC");
        break;
    case HEXadecimal:
        output = QString(":FORM:SREG HEX");
        break;
    case OCTal:
        output = QString(":FORM:SREG OCT");
        break;
    case BINary:
        output = QString(":FORM:SREG BIN");
        break;
    default:
        output = QString(":FORM:SREG ASC");
        break;
    }

    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Select terminals connections rear or front
 *
 * @param state A bool to enable rear terminals.
 */

void Scpi::terminalsRoute(const bool state)
{
    QString output;
    if(state)
        output = QString(":ROUT:TERM REAR");
    else
        output = QString(":ROUT:TERM FRON");

    qDebug() << output.toLocal8Bit().data();
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}

/**
 * @brief Program arm layer counter to infinite counts.
 */

void Scpi::armCounterInfinite()
{
    QString output = QString(":ARM:COUN INF");
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
}


/**
  * @brief Reads Status Byte Register.
  *
  * @return An integer containing the Status Byte info.
  */

int Scpi::stbQuery()
{
    QString output = QString( "*STB?" );
    qDebug() << output.toLocal8Bit().data();
#ifndef TEST
    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );

    QByteArray statusRegister = Gpib::read().toByteArray();
    int i = 0;
    while( statusRegister.at( i ) != '\n' )
        i++;

    statusRegister.truncate(i);
    return statusRegister.toInt();
#else
    return 0;
#endif
}

/**
  * @brief Reads and resets Standard Event Status Register.
  *
  * @return A QVariant containing the Status Byte previous reset.
  */

QVariant Scpi::esrQuery()
{
    QString output = QString( "*ESR?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read();
}

/**
  * @brief Reads and resets Operation Event Register.
  *
  * @return A QVariant containing the Operation Event Register status previous reset.
  */

QVariant Scpi::oerQuery()
{
    QString output = QString( ":STAT:OPER:EVEN?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read();
}

/**
  * @brief Reads and resets Measurement Event Register.
  *
  * @return A QVariant containing the Measurement Event Register status previous reset.
  */

QVariant Scpi::merQuery()
{
    QString output = QString( ":STAT:MEAS:EVEN?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read();
}

/**
  * @brief Reads and resets Questionable Event Register.
  *
  * @return A QVariant containing the Questionable Event Register status previous reset.
  */

QVariant Scpi::qerQuery()
{
    QString output = QString( ":STAT:QUES:EVEN?" );
    qDebug() << output.toLocal8Bit().data();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read();
}

/**
  * @brief Trigger and reads Status Byte Register.
  *
  * @return A Qstring cointaining the last error read from the error queue.
  */

QString Scpi::queueErrorQuery()
{
    QString output = QString( ":STAT:QUE?" );
    qDebug() << output.toLocal8Bit().data();

    allResgistersQueryTest();

    if( Gpib::isNoError() )
        Gpib::write( output.toLocal8Bit().data() );
    return Gpib::read().toString();
}

/**
  * @brief Use to read Status and Standard registers and masks (enable)
  */

void Scpi::allResgistersQueryTest()
{
    // Status byte register
    // Event
    //QTest::qSleep(1000);
    int statusR = stbQuery();
    statusR = statusR +1 -1;

    // Enable
    //QTest::qSleep(1000);
    if( Gpib::isNoError() )
        Gpib::write("*SRE?");
    QString statusE = Gpib::read().toString();
    statusE = statusE.append("!!");

    // Standard register
    // Event
    //QTest::qSleep(1000);
    QString standardR = esrQuery().toString();
    standardR = standardR.append("!!");

    // Enable
    if( Gpib::isNoError() )
        Gpib::write("*ESE?");
    QString standardE = Gpib::read().toString();
    statusE = standardE.append("!!");

}



