#ifndef SCPICOMMANDFACTORY_H
#define SCPICOMMANDFACTORY_H

#include <QDebug>
#include <QVariant>
#include <QObject>

class SCPICommandFactory : public QObject
{
    Q_OBJECT
public:
    SCPICommandFactory();
    ~SCPICommandFactory();


    QString reset();

    QString setInVoltageSourceMode();
    QString setInCurrentSourceMode();
    QString setInFixedVoltageSourceMode();
    QString setInFixedCurrentSourceMode();

    QString setInVoltageMeasureMode();
    QString setInCurrentMeasureMode();

    QString setVoltageSourceRange( double setVoltageSourceRange );
    QString setCurrentSourceRange( double setCurrentSourceRange );
    QString setCurrentSourceRangeToMin();

    QString disableBufferOfReadings();
    QString enableBufferOfReadings();
    QString clearBufferOfReadings();
    QString clearTriggerCountBuffer();
    QString setBufferOfReadingsSize(int _size);

    QString resetTimeStamps();
    QString configTimeStampAsAbsolute();
    QString configTimeStampAsDelta();
    QString turnOffConcurrentFunctions();

    QString concurrentMeasure( bool status);

    QString setCurrentCompliance( double setCurrentCompliance );
    QString setVoltageCompliance( double setVoltageCompliance );

    QString setNplc( QString nplc );

    QString setVoltageMeasureRangeInAuto( bool status );
    QString setVoltageMeasureRange( double measureRange );
    QString setCurrentMeasureRangeInAuto( bool status );
    QString setCurrentMeasureRange( double measureRange );

    QString enableFilter( bool status );
    QString setFilterCount( int setFilterCount );
    QString setFilterType( int filterTypeIndex );

    QString setVoltageSourceLevel( double sourceLevel );
    QString setCurrentSourceLevel( double sourceLevel );

    QString setPulseWidth( double width );
    QString setPulseDelay( double pulseDelay );

    QString enableOutput( bool status );

    QString readQuery();
    QString fetchQuery();
    QString dataQuery();
    QString idnQuery();

    QString initTrigger();

    QString enableMeasureFunctionsSCPI(const QString parameters);

    QString displayTextState(const int window, bool state);
    QString displayText(const int window, const QString text);

    QString setTriggerCount(int triggerCount);

    QString setVoltageSweepStart(const double sweepVoltageStart);
    QString setVoltageSweepStop(const double sweepVoltageStop);

    QString setCurrentSweepStart(const double sweepCurrentStart);
    QString setCurrentSweepStop(const double sweepCurrentStop);

    QString setVoltageSweepStep(const double sweepVoltageStep);
    QString setCurrentSweepStep(const double sweepCurrentStep);

    QString setVoltageSweepMode();
    QString setCurrentSweepMode();

    QString setSweepType( const int sweepType );
    QString setSweepPoints( const int sweepPoints );

    QString clearStatus();

    QString programSrqr(const int config);
    QString programSer(const int config);
    QString programOer(const int config);
    QString programMer(const int config);
    QString programQer(const int config);

    QString formatStatusRegister(const int format);

    QString terminalsRoute( const bool state );

    QString armCounterInfinite();

    };

#endif // SCPICOMMANDFACTORY_H
