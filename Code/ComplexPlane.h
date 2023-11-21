#include <SFML/Graphics.hpp> 
#include <iostream>
using namespace std;

using sf::RenderTarget;
using sf::RenderStates;
using sf::Vector2i;
using sf::Vector2f;
using sf::VertexArray;
using sf::Uint8;
using sf::Text;

const unsigned int MAX_ITER = 64;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;



class ComplexPlane
{ 

    enum class State 
    {
        CALCULATING,
        DISPLAYING
    };

    public:
    
    ComplexPlane(int pixelWidth, int pixelHeight);
    void draw(RenderTarget& target, RenderStates states) const;
    void zoomIn();
    void zoomOut();
    void setCenter(Vector2i mousePixel);
    void setMouseLocation(Vector2i mousePixel);
    void loadText(Text& text);
    void updateRender();

    private:
    int countIterations(Vector2f coord);
    void iterationsToRGB(size_t count, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);

    //m stands for monitor, ex monitor aspectRatio
    VertexArray m_vArray;
    State m_state;
    Vector2f m_mouseLocation;
    Vector2i m_pixel_size;
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    int m_ZoomCount;
    float m_aspectRatio;
};