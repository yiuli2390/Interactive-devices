
typedef struct {
    byte pump;
    byte high;
    byte low;
    int  highTime;
    int  lowTime;
    int  numSteps;
    int  initialDelay;
    boolean startLow;
    int  currentStep;
} pattern;

typedef struct {
    byte* pumps;
    byte* powers;
    int*  delays;
    int   currentIndex;
    int   initialDelay;
} sequence;

void main()
{

}

pattern* nextPattern(pattern** patternArr, int sizeArr)
{
    pattern* current;
    pattern* soonest;
    int minTime = 0;
    int time = 0;

    for(int i = 0; i < sizeArr; i++)
    {
        current = patternArr[i];

        if(current.startHigh)
            time = ceil( current->currentStep/2) * high + floor(current->currentStep/2) * current->low;
        else
            time = floor(current->currentStep/2) * high + ceil( current->currentStep/2) * current->low;

        time += current->initalDelay;        

        if(time < minTime)
            soonest = current;
    }
    return soonest;
}

boolean nextHigh(pattern* pat)
{
    if pattern->startHigh && pattern->currentStep % 2 == 0
        return false;
    if pattern->startHigh && pattern->currentStep % 2 == 1
        return true;
    if !pattern->startHigh && pattern->currentStep % 2 == 0
        return true;
    if !pattern->startHigh && pattern->currentStep % 2 == 1
        return false;
}

byte getNextPower(pattern* pat)
{
    if nextHigh(pattern)
        return pat->high;
    else
        return pat->low;  
}

int getNextDelay(pattern* pat)
{
    if nextHigh(pattern)
        return pat->highTime;
    else
        return pat->lowTime;
}

int getNextDelay(pattern* pat)
{
    if nextHigh(pattern)
        return pat->lowTime;
    else
        return pat->highTime;
}

void compilePatterns(pattern** patternArr, int sizeArr)
{
    sequence combined = malloc(sizeof(sequence));
    pattern* NextPattern;
    int nextPatternIndex;
    int totalSteps = 0;

    for(int i = 0; i < sizeArr; i++)
    {
        totalSteps += patternArr(i)->numSteps;
    }

    combined->pumps  = malloc(sizeof(byte) * totalSteps);
    combined->powers = malloc(sizeof(byte) * totalSteps);
    combined->delays = malloc(sizeof(int) * totalSteps);
    combined->currentIndex = 0;

    //TODO: Do first manually?
    
    for(int i = 1; i < totalSteps; i++)
    {
        nextPattern = nextTime(patternArr, sizeArr);
        combined->pumps[i]  = nextPattern->pump;
        combined->powers[i] = getNextPower(nextPattern);
        combined->delays[i] = getNextDelay(nextPattern) - getPrevDelay(nextPattern);
    }
}
