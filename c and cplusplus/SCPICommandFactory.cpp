#include "../GPIB/SCPICommandFactory.h"

#include "./Instruments/keithley/sourceMeters/K24xxConfigurationParameters.h"

/**
  * @brief Constructor
  */
SCPICommandFactory::SCPICommandFactory()
{
}

SCPICommandFactory::~SCPICommandFactory()
{
}

/**
 * @brief Reset the device. Restore GPIB defaults values.
 */
QString SCPICommandFactory::reset()
{
    QString output = "*RST";

    return output;
}

/**
 * @brief Disable the Buffer of readings.
 * This action command is used to disable the buffer of readings.
 */
QString SCPICommandFactory::disableBufferOfReadings()
{
    QString output = ":TRAC:FEED:CONT NEVER";
    return output;
}

/**
 * @brief Enable the Buffer of readings.
 * This action command is used to enable the buffer of readings.
 */
QString SCPICommandFactory::enableBufferOfReadings()
{
    QString output = ":TRAC:FEED:CONT NEXT";

    return output;
}

/**
 * @brief Clear the Buffer of readings.
 * This action command is used to clear the buffer of readings. If you do
 * not clear the buffer, a subsequent store will overwrite the old read-
 * ings.
 */
QString SCPICommandFactory::clearBufferOfReadings()
{
    QString output = ":TRAC:CLE";
    return output;
}
/**
 * @brief Clear the Trigger Count Buffer.
 * This action command is used to clear the trigger count buffer.
 * More info = http://www.keithley.com/data?asset=3814
 */
QString SCPICommandFactory::clearTriggerCountBuffer()
{
    QString output = ":TRIG:CLE";

    return output;
}
/**
 * @brief Set the size of the Buffer of readings.
 * This command is used to specify the size of the buffer
 */

QString SCPICommandFactory::setBufferOfReadingsSize(int _size){
    QString output = QString(":TRAC:POIN %1").arg( _size );

    return output;
}

/**
 * @brief Set the timeStamps timer to zero.
 * This command is used to set to zero the timer that is used to mark the timestamps at every measure
 */
QString SCPICommandFactory::resetTimeStamps()
{
    QString output = QString( "SYST:TIME:RES" );

    return output;
}

/**
 * @brief Set the timeStamps timer to absolute format.
 * This command is used to set the format of the timestamp to absolute.
 */
QString SCPICommandFactory::configTimeStampAsAbsolute()
{
    QString output = QString( ":TRAC:TST:FORM ABS" );

    return output;
}

/**
 * @brief Set the timeStamps timer to delta format.
 * This command is used to set the format of the timestamp to delta.
 */
QString SCPICommandFactory::configTimeStampAsDelta()
{
    QString output = QString( ":TRAC:TST:FORM DELT" );

    return output;
}


/**
 * @brief Turn off concurrent functions
 *
 */
QString SCPICommandFactory::turnOffConcurrentFunctions()
{
    QString output = QString(":SENS:FUNC:CONC OFF");

    return output;
}

/**
 * @brief Voltage source mode.
 */
QString SCPICommandFactory::setInVoltageSourceMode()
{
    QString output = ":SOUR:FUNC VOLT";

    return output;
}

/**
 * @brief Current source mode.
 */
QString SCPICommandFactory::setInCurrentSourceMode()
{
    QString output = ":SOUR:FUNC CURR";

    return output;
}

/**
 * @brief Fixed Voltage source mode.
 */
QString SCPICommandFactory::setInFixedVoltageSourceMode()
{
    QString output = ":SOUR:VOLT:MODE FIXED";

    return output;
}

/**
 * @brief Fixed Current source mode.
 */
QString SCPICommandFactory::setInFixedCurrentSourceMode()
{
    QString output = ":SOUR:CURR:MODE FIXED";

    return output;
}

/**
 * @brief Voltage measure mode.
 */
QString SCPICommandFactory::setInVoltageMeasureMode()
{
    QString output = ":SENS:FUNC 'VOLT'";

    return output;
}

/**
 * @brief Current source mode.
 */
QString SCPICommandFactory::setInCurrentMeasureMode()
{
    QString output = ":SENS:FUNC 'CURR:DC'";

    return output;
}

/**
 * @brief Voltage source range selection.
 *
 * @param voltageSourceRange Is a double containing the voltage source Range value.
 */
QString SCPICommandFactory::setVoltageSourceRange(double voltageSourceRange)
{
    QString output = QString(":SOUR:VOLT:RANG %1").arg(voltageSourceRange);

    return output;
}

/**
 * @brief Current source range selection.
 *
 * @param currentSourceRange Is a double containing the current source Range value.
 */
QString SCPICommandFactory::setCurrentSourceRange(double currentSourceRange)
{
    QString output = QString(":SOUR:CURR:RANG %1").arg(currentSourceRange);

    return output;
}

/**
 * @brief Current source range to min.
 *
 */
QString SCPICommandFactory::setCurrentSourceRangeToMin()
{
    QString output = QString(":SOUR:CURR:RANG MIN");

    return output;
}


/**
 * @brief Enable or disable concurrent meausures.
 *
 * @param satus Is a bool that enables (TRUE) or disables (FALSE) concurrent measures.
 */
QString SCPICommandFactory::concurrentMeasure( bool status )
{
    QString output;
    if( status )
        output = ":SENS:FUNC:CONC ON";
    else
        output = ":SENS:FUNC:CONC OFF";


    return output;
}

/**
  * @brief Set current sense compliance.
  *
  * @param currentCompliance Is a double that contains the limit corrent for the desired measure.
  */

QString SCPICommandFactory::setCurrentCompliance(double currentCompliance)
{
    QString output = QString(":SENS:CURR:PROT %1").arg( currentCompliance );

    return output;
}

/**
  * @brief Set voltage sense compliance.
  *
  * @param voltageCompliance Is a double that contains the voltage limit for the desired measure.
  */

QString SCPICommandFactory::setVoltageCompliance(double voltageCompliance)
{
    QString output = QString(":SENS:VOLT:PROT %1").arg( voltageCompliance );

    return output;
}

/**
  * @brief Set integration time.
  *
  * @param nplc A QString that holds the nplc value retrieved from the UI.
  */

QString SCPICommandFactory::setNplc(QString nplc)
{
    /* ...VOLT:NPLC is used as instruction for any kind of measure.
    (Keithley Manual) Note that this is a global command. Thus, if you set the speed
    for voltage measurements to 10 PLC, then current and resistance will also set to
    10 PLC.*/
    QString output = ":SENS:VOLT:NPLC " + nplc;

    return output;
}

/**
  * @brief Disable or enable auto voltage range.
  *
  * @param status Is a bool that contains wether or not enable or disable auto voltage range.
  */

QString SCPICommandFactory::setVoltageMeasureRangeInAuto(bool status)
{
    QString output;
    if( status )
        output = ":SENS:VOLT:RANG:AUTO ON";
    else
        output = ":SENS:VOLT:RANG:AUTO OFF";


    return output;
}

/**
  * @brief Set voltage measure range.
  *
  * @param
  */

QString SCPICommandFactory::setVoltageMeasureRange(double measureRange)
{
    QString output = QString(":SENS:VOLT:RANG %1").arg( measureRange );

    return output;
}

/**
  * @brief Disable or enable auto current range.
  *
  * @param status Is a bool that contains wether or not enable or disable auto current range.
  */

QString SCPICommandFactory::setCurrentMeasureRangeInAuto(bool status)
{
    QString output;
    if( status )
        output = ":SENS:CURR:RANG:AUTO ON";
    else
        output = ":SENS:CURR:RANG:AUTO OFF";


    return output;
}

/**
  * @brief Set current measure range.
  *
  * @param measureRange
  */

QString SCPICommandFactory::setCurrentMeasureRange(double measureRange)
{
    QString output = QString(":SENS:CURR:RANG %1").arg( measureRange );

    return output;
}

/**
  * @brief Disable or enable filter
  *
  * @param status Is a bool that contains wether or not enable the filter
  */
QString SCPICommandFactory::enableFilter(bool status)
{
    QString output;
    if( status )
        output = ":SENS:AVER:STAT ON";
    else
        output = ":SENS:AVER:STAT OFF";


    return output;
}

/**
  * @brief Set filter count.
  *
  * @param filterCount A int that holds the number of filter counts.
  */

QString SCPICommandFactory::setFilterCount(int filterCount)
{
    QString output;
    output = QString(":SENS:AVER:COUN %1").arg( filterCount ) ;

    return output;
}

/**
  * @brief Set filter type.
  *
  * @param filterTypeIndex A int that contains an index that differences from different filter
  * types: EXPonetial, NORMal, REPeat, MOVing.
  */

QString SCPICommandFactory::setFilterType(int filterTypeIndex)
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

    return output;
}

/**
  * @brief Set voltage source level.
  *
  * @param sourceLevel A double that contains the desired voltage source level for the instrument.
  */

QString SCPICommandFactory::setVoltageSourceLevel(double sourceLevel)
{
    QString output;
    output = QString( ":SOUR:VOLT:LEV %1" ).arg( sourceLevel ) ;

    return output;
}

/**
  * @brief Set current source level.
  *
  * @param sourceLevel A double that contains the desired current (in Amps) source level for the instrument.
  */

QString SCPICommandFactory::setCurrentSourceLevel(double sourceLevel)
{
    QString output;
    output = QString( ":SOUR:CURR:LEV %1" ).arg( sourceLevel ) ;

    return output;
}

/**
  * @brief Set pulse width.
  *
  * @param sourceLevel A double that contains the pulse width from 0.15ms to 5ms.
  */

QString SCPICommandFactory::setPulseWidth(double width)
{
    QString output;
    output = QString( ":SOUR:PULS:WIDT %1" ).arg( width ) ;

    return output;
}

/**
  * @brief Set pulse width.
  *
  * @param sourceLevel A double that contains the pulse width from 0.15ms to 5ms.
  */

QString SCPICommandFactory::setPulseDelay( double pulseDelay )
{
    QString output;
    output = QString( ":SOUR:PULS:DEL %1" ).arg( pulseDelay ) ;

    return output;
}

/**
  * @brief Enable or disable the instrument output.
  *
  * @param output A boolean that holds wether or not to turn off or on the instrument output.
  */

QString SCPICommandFactory::enableOutput(bool status)
{
    QString output;
    if( status )
        output = ":OUTP:STAT ON";
    else
        output = ":OUTP:STAT OFF";


    return output;
}


/**
  * @brief gets the IDN of the instrument.
  */

QString SCPICommandFactory::idnQuery()
{
    QString output = QString( "*IDN?" );

    return output;
}

/**
  * @brief Trigger and adquires readings.
  */

QString SCPICommandFactory::readQuery()
{
    QString output = QString( ":READ?" );

    return output;
}

/**
  * @brief get data from instrument buffer.
  */

QString SCPICommandFactory::dataQuery()
{
    QString output = QString( ":TRAC:DATA?" );

    return output;
}

/**
  * @brief Fetch data from instrument buffer.
  */

QString SCPICommandFactory::fetchQuery()
{
    QString output = QString( ":FETC?" );

    return output;
}

/**
  * @brief Sends :INIT command to trigger the device measure.
  */

QString SCPICommandFactory::initTrigger()
{
    QString output = QString( ":INIT");

    return output;
}


/**
  * @brief Enable measure functions.
  *
  * @param parameters A QString that includes all the functions to enable.
  */

QString SCPICommandFactory::enableMeasureFunctionsSCPI( const QString parameters )
{
    QString output = QString( ":SENS:FUNC:ON " + parameters );

    return output;
}

/**
  * @brief Disables or enables text messages for displays.
  *
  * @param window A int used to choose between top and bottom display.
  * @param state A bool to turn On or Off the display text messages mode.
  */

QString SCPICommandFactory::displayTextState( const int window, bool state )
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


    return output;
}

/**
  * @brief Display custom texts.
  *
  * @param window A int used to choose between top and bottom display.
  * @param parameters A QString that includes the text to display.
  */

QString SCPICommandFactory::displayText( const int window, const QString text )
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


    return output;

}

/**
  * @brief Set trigger count.
  *
  * @param triggerCount A integer holding the number of trigger counts betwee 1 to 2500.
  */
QString SCPICommandFactory::setTriggerCount( int triggerCount )
{
    QString output;

    // Avoiding overcome the maximum count trigger.
    if( triggerCount > 2500 || triggerCount < 1)
        triggerCount = 2500;

    output = QString( ":TRIG:COUN %1" ).arg( triggerCount ) ;

    return output;
}

/**
  * @brief Set sweep voltage starting point.
  *
  * @param sweepVoltageStart A double holding the sweep voltage starting value.
  */
QString SCPICommandFactory::setVoltageSweepStart(const double sweepVoltageStart)
{
    QString output;

    output = QString( ":SOUR:VOLT:STAR %1" ).arg( sweepVoltageStart ) ;

    return output;
}

/**
  * @brief Set sweep voltage stoping point.
  *
  * @param sweepVoltageStart A double holding the sweep voltage stoping value.
  */
QString SCPICommandFactory::setVoltageSweepStop(const double sweepVoltageStop)
{
    QString output;

    output = QString( ":SOUR:VOLT:STOP %1" ).arg( sweepVoltageStop ) ;

    return output;
}

/**
  * @brief Set sweep current starting point.
  *
  * @param sweepCurrentStart A double holding the sweep current starting value.
  */
QString SCPICommandFactory::setCurrentSweepStart(const double sweepCurrentStart)
{
    QString output;

    output = QString( ":SOUR:CURR:STAR %1" ).arg( sweepCurrentStart ) ;

    return output;
}

/**
  * @brief Set sweep current stoping point.
  *
  * @param sweepCurrentStop A double holding the sweep current stoping value.
  */
QString SCPICommandFactory::setCurrentSweepStop(const double sweepCurrentStop)
{
    QString output;

    output = QString( ":SOUR:CURR:STOP %1" ).arg( sweepCurrentStop );

    return output;
}

/**
  * @brief Set sweep voltage step value.
  *
  * @param sweepVoltageStep A double holding the sweep voltage step value.
  */
QString SCPICommandFactory::setVoltageSweepStep(const double sweepVoltageStep)
{
    QString output;

    output = QString( ":SOUR:VOLT:STEP %1" ).arg( sweepVoltageStep );

    return output;
}

/**
  * @brief Set sweep current step value.
  *
  * @param sweepCurrentStep A double holding the sweep current step value.
  */
QString SCPICommandFactory::setCurrentSweepStep(const double sweepCurrentStep)
{
    QString output;

    output = QString( ":SOUR:CURR:STEP %1" ).arg( sweepCurrentStep );

    return output;
}

/**
  * @brief Set voltage sweep mode.
  */
QString SCPICommandFactory::setVoltageSweepMode()
{
    QString output = ":SOUR:VOLT:MODE SWE";

    return output;
}

/**
  * @brief Set current sweep mode.
  */
QString SCPICommandFactory::setCurrentSweepMode()
{
    QString output = ":SOUR:CURR:MODE SWE";

    return output;
}

/**
  * @brief Set sweep mode.
  *
  * @param sweepMode An int that holds weather the sweep is linear or logarithmic.
  */
QString SCPICommandFactory::setSweepType(const int sweepType)
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

    return output;
}

/**
  * @brief Set the number of sweep points.
  *
  * @param setSweepPoints An int that holds the number of points for a sweep.
  */
QString SCPICommandFactory::setSweepPoints(const int sweepPoints)
{
    QString output;

    output = QString( ":SOUR:SWE:POIN %1" ).arg( sweepPoints );

    return output;
}


/**
 * @brief Clear Status. Clears all event registers and Error Queue.
 */

QString SCPICommandFactory::clearStatus()
{
    QString output = "*CLS";

    return output;
}

/**
 * @brief Program Service Request enable register
 *
 * @param config An int that holds the configuration value for SRE.
 */

QString SCPICommandFactory::programSrqr(const int config)
{
    QString output = QString("*SRE %1").arg(config);

    return output;
}

/**
 * @brief Program the Standard Event Enable Register
 *
 * @param config An int that holds the configuration value for Standard Event Enable Register.
 */

QString SCPICommandFactory::programSer(const int config)
{
    QString output = QString("*ESE %1").arg(config);

    return output;
}

/**
 * @brief Program the Operation Enable Register
 *
 * @param config An int that holds the configuration value for Operation Enable Register.
 */

QString SCPICommandFactory::programOer(const int config)
{
    QString output = QString(":STAT:OPER:ENAB %1").arg(config);

    return output;
}

/**
 * @brief Program the Measurement Enable Register
 *
 * @param config An int that holds the configuration value for Measurement Enable Register.
 */

QString SCPICommandFactory::programMer(const int config)
{
    QString output = QString(":STAT:MEAS:ENAB %1").arg(config);

    return output;
}

/**
 * @brief Program the Questionable Enable Register
 *
 * @param config An int that holds the configuration value for Questionable Enable Register.
 */

QString SCPICommandFactory::programQer(const int config)
{
    QString output = QString(":STAT:QUES:ENAB %1").arg(config);

    return output;
}

/**
 * @brief Select status register format
 *
 * @param format An int used as an index to choose between formats: ASCii, HEXadecimal, OCTal, BINary
 */

QString SCPICommandFactory::formatStatusRegister(const int format)
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


    return output;
}

/**
 * @brief Select terminals connections rear or front
 *
 * @param state A bool to enable rear terminals.
 */

QString SCPICommandFactory::terminalsRoute(const bool state)
{
    QString output;
    if(state)
        output = QString(":ROUT:TERM REAR");
    else
        output = QString(":ROUT:TERM FRON");


    return output;
}

/**
 * @brief Program arm layer counter to infinite counts.
 */

QString SCPICommandFactory::armCounterInfinite()
{
    QString output = QString(":ARM:COUN INF");

    return output;
}

