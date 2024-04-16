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

        int *  getSignalBuffer()            {  return signalBuffer;  }
        unsigned int getBufferSize()        {  return bufferSize;    }


    protected:

    private:

        int *signalBuffer = nullptr;
        unsigned int bufferSize = 0;
};

#endif // SIGNALGENERATOR_H
