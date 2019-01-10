#ifndef SCPI_H
#define SCPI_H

#include "../GPIB/gpib.h"

#include <QDebug>
#include <QVariant>
#include <QObject>

class Scpi : public QObject
{
    Q_OBJECT
public:
    Scpi();
    ~Scpi();

    void write(QString);

    void reset();

    void setInVoltageSourceMode();
    void setInCurrentSourceMode();
    void setInFixedVoltageSourceMode();
    void setInFixedCurrentSourceMode();

    void setInVoltageMeasureMode();
    void setInCurrentMeasureMode();

    void setVoltageSourceRange( double setVoltageSourceRange );
    void setCurrentSourceRange( double setCurrentSourceRange );
    void setCurrentSourceRangeToMin();

    void concurrentMeasure( bool status);

    void setCurrentCompliance( double setCurrentCompliance );
    void setVoltageCompliance( double setVoltageCompliance );

    void setNplc( QString nplc );

    void setVoltageMeasureRangeInAuto( bool status );
    void setVoltageMeasureRange( double measureRange );
    void setCurrentMeasureRangeInAuto( bool status );
    void setCurrentMeasureRange( double measureRange );

    void enableFilter( bool status );
    void setFilterCount( int setFilterCount );
    void setFilterType( int filterTypeIndex );

    void setVoltageSourceLevel( double sourceLevel );
    void setCurrentSourceLevel( double sourceLevel );

    void setPulseWidth( double width );
    void setPulseDelay( double pulseDelay );

    void enableOutput( bool status );

    QVariant readQuery(const int size = 42);
    QVariant fetchQuery(const int size = 42);
    QVariant dataQuery(const int size = 42);
    QVariant idnQuery( const int size = 42);

    void initTrigger();

    void enableMeasureFunctionsSCPI(const QString parameters);

    void displayTextState(const int window, bool state);
    void displayText(const int window, const QString text);

    void setTriggerCount(int triggerCount);

    void setVoltageSweepStart(const double sweepVoltageStart);
    void setVoltageSweepStop(const double sweepVoltageStop);

    void setCurrentSweepStart(const double sweepCurrentStart);
    void setCurrentSweepStop(const double sweepCurrentStop);

    void setVoltageSweepStep(const double sweepVoltageStep);
    void setCurrentSweepStep(const double sweepCurrentStep);

    void setVoltageSweepMode();
    void setCurrentSweepMode();

    void setSweepType( const int sweepType );
    void setSweepPoints( const int sweepPoints );

    void testInstrunction(const char * instruction);

    void clearStatus();

    void programSrqr(const int config);
    void programSer(const int config);
    void programOer(const int config);
    void programMer(const int config);
    void programQer(const int config);

    void formatStatusRegister(const int format);

    void terminalsRoute( const bool state );

    void armCounterInfinite();

    int stbQuery();

    QVariant esrQuery();
    QVariant oerQuery();
    QVariant merQuery();
    QVariant qerQuery();

    QString queueErrorQuery();

    void allResgistersQueryTest();

    };

#endif // SCPI_H
