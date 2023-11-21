#include "ComplexPlane.h" 
#include <cmath>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{

}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{

}

void ComplexPlane::updateRender()
{

}


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
