#ifndef SIGNALGENERATOR_H
#define SIGNALGENERATOR_H

#define MAX_SAMPLE_SIZE  10000

class SignalGenerator
{
    public:
        SignalGenerator();
        virtual ~SignalGenerator();

        bool generate(int sampleSize);

        bool isValidSampleSize(int sampleSize);

    protected:

    private:

        int *signalBuffer = nullptr;
};

#endif // SIGNALGENERATOR_H
