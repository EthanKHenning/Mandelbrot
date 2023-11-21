const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum class State 
{
    CALCULATING,
    DISPLAYING
};

class ComplexPlane
{ 
    public:
    ComplexPlane();

    private:
    int countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);

    VertexArray m_vArray;
    State m_state;
    Vector2f m_mouseLocation;
    Vector2i m_pixel_size;
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    int m_ZoomCount;
    float m_aspectRatio;
};