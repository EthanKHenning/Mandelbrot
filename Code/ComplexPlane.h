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

//max_iter should be 500
const unsigned int MAX_ITER = 100;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;



class ComplexPlane : public sf::Drawable
{ 

    enum class State 
    {
        CALCULATING,
        DISPLAYING
    };

    public:
    
    //Note to self
    //Vector2f f = float
    //Vector2i i = int
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
    void iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b);
    Vector2f mapPixelToCoords(Vector2i mousePixel);

    //m stands for monitor, ex monitor aspectRatio
    VertexArray m_vArray;
    State m_state;
    Vector2i m_pixelWidth;
    Vector2f m_mouseLocation;
    Vector2i m_pixel_size;
    Vector2f m_plane_center;
    Vector2f m_plane_size;
    int m_ZoomCount;
    float m_aspectRatio;
};