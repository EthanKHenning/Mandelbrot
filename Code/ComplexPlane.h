const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

class ComplexPlane
{ 
    public:
    enum class State 
    {
        CALCULATING,
        DISPLAYING
    };

    ComplexPlane();

    protected:
    int pixelWidth;
    int pixelHeight;
};