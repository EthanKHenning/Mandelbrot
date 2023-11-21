#include "ComplexPlane.h" 
#include <cmath>
#include <sstream>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixelWidth = {pixelWidth, pixelHeight};
    m_aspectRatio = static_cast<double>(pixelHeight/pixelWidth);
    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
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
        // Double for loop, iterates through all pixels
        for (float i = 0; i < m_pixelWidth.y; ++i)
        {
            for (float j = 0; j < m_pixelWidth.x; ++j)
            {
                m_vArray[j + i * m_pixelWidth.x].position = { j, i };

                // Use ComplexPlane::mapPixelToCoords to find the Vector2f coordinate
                Vector2f coordinate = mapPixelToCoords(Vector2i(j, i));

                // Call ComplexPlane::countIterations
                int iterations = countIterations(coordinate);
                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                // Sets the color for the point/vertex
                m_vArray[j + i * m_pixelWidth.x].color = { r, g, b};
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
    m_plane_size = {xSize, ySize};
    m_state = State::CALCULATING;
}


void ComplexPlane::zoomOut()
{
    m_ZoomCount--;
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
    m_plane_size = {xSize, ySize};
    m_state = State::CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
    stringstream strm;

    strm << "Mandelbrot Set" << endl
         << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")" << endl
         << "Cursor: (" << m_mouseLocation.x << ", " << m_mouseLocation.y << ")" << endl
         << "Left-click to Zoom in" << endl
         << "Right-click to Zoom out";

    //Sets the text to whatever is put in strm
    text.setString(strm.str());
}


int ComplexPlane::countIterations(Vector2f coord)
{
    return 500;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{

    if (count == MAX_ITER)
    {
        r = 250;
        g = 0;
        b = 0;
    }

    else if ((count < MAX_ITER) && (count > (MAX_ITER / 1.25)))
    {
        r = 200;
        g = 0;
        b = 0;
    }

    else if ((count < (MAX_ITER/1.25)) && (count > (MAX_ITER/1.5)))
    {
        r = 200;
        g = 100;
        b = 50;
    }
    else if ((count < (MAX_ITER / 1.5)) && (count > (MAX_ITER / 1.75)))
    {
        r = 0;
        g = 200;
        b = 0;
    }
    else if ((count < (MAX_ITER / 1.75)) && (count > (MAX_ITER / 2)))
    {
        r = 0;
        g = 100;
        b = 150;
    }
    else
    {
        r = 0;
        g = 0;
        b = 250;
    }

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) {

    float x, y, mX, mY;
    //declared in order of use in equation, also best written as floats as Vector2f holds floats and it keeps things more consistent
    float a, b, c, d;
    
    //in mousPixel they are declard as Vector2i, the i stands for int
    x = static_cast<float>(mousePixel.x);
    y = static_cast<float>(mousePixel.y);

    a = 0.0f;
    b = static_cast<float>(m_plane_size.x);
    c = m_plane_center.x - m_plane_size.x / 2.0f;
    d = 2.0f;

    mX = ((x - a) / (b - a)) * (d - c) + c;

    b = static_cast<float>(m_pixel_size.y);
    a = 0.0f;

    c = m_plane_center.y - m_plane_size.y / 2.0f;
    mY = ((y - a) / (b - a)) * (d - c) + c;

    Vector2f mousePixelF = {mX, mY};
    cout << "center : " << mX << " " << mY;

    return mousePixelF;

}
