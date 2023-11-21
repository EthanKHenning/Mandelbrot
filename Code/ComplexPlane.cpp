#include "ComplexPlane.h" 
#include <cmath>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixelWidth(pixelWidth, pixelHeight);
    m_aspectRatio = pixelHeight/pixelWidth;
    m_plane_center(0, 0);
    m_plane_size(BASE_WIDTH, BASE_HEIGHT * m_aspectRatio);
    m_ZoomCount = 0;
    m_state = State::CALCULATING;
    m_vArray.setPrimitiveType(sf::Points);
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(m_vArray);
}


void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        // Double for loop allows us to iterate through all pixels
        for (int i = 0; i < m_pixel_size.y; ++i)
        {
            for (int j = 0; j < m_pixel_size.x; ++j)
            {
                m_vArray[j + i * m_pixel_size.x].position = { j, i };

                // Use ComplexPlane::mapPixelToCoords to find the Vector2f coordinate
                Vector2f coordinate = mapPixelToCoords(Vector2i(j, i));

                // Call ComplexPlane::countIterations
                int iterations = countIterations(coordinate);
                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                // Sets the color for the point/vertex
                m_vArray[j + i * m_pixel_size.x].color = { 255, r, g, b };  
            }
        }

        // Set the state to DISPLAYING
        m_state = State::DISPLAYING;
    }
}

//keeps track of each time the user scrolls the mouse wheel up, for each upward scroll it will generate a new version of the plane enlarged proprotionally
//to the amount of scrolls
void ComplexPlane::zoomIn()
{
    m_ZoomCount++;
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
    m_plane_size = sf::Vector2f(xSize, ySize);
    m_state = State::CALCULATING;
}


void ComplexPlane::zoomOut()
{
    m_ZoomCount--;
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
    m_plane_size = sf::Vector2f(xSize, ySize);
    m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{

}

void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{

}

void ComplexPlane::loadText(Text& text)
{

}


size_t ComplexPlane::countIterations(Vector2f coord)
{

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

}

