#include "SignalGenerator.h"

SignalGenerator::SignalGenerator()
{
    //ctor
}

SignalGenerator::~SignalGenerator()
{
    if (signalBuffer != nullptr)   delete signalBuffer;

}

bool SignalGenerator::isValidSampleSize(int sampleSize)
{
    if (sampleSize <= 0 || sampleSize > MAX_SAMPLE_SIZE)
       return false;
    else
       return true;
}


bool SignalGenerator::generate(int sampleSize)
{

   if ( !isValidSampleSize(sampleSize) )  return false;

    // Make sure that any previous data is cleaned first...
    if (signalBuffer != nullptr)   delete signalBuffer;

    signalBuffer = new int[sampleSize];

    for (int i=0;i<sampleSize;i++)
    {
        signalBuffer[i] = 0;
    }

    return true;
}

