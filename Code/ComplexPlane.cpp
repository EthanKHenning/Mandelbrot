#include "ComplexPlane.h" 
#include <cmath>
#include <sstream>

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = {pixelWidth, pixelHeight};

    //if not converted to double or float before division the answer will be an int and the decimal will be cut off
    m_aspectRatio = static_cast<double>(pixelHeight)/static_cast<double>(pixelWidth);

    m_plane_center = {0, 0};
    m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
    m_ZoomCount = 0;
    m_state = State::CALCULATING;

    //each vertex is a point/pixel, each points color will be decided independently
    m_vArray.setPrimitiveType(sf::Points);

    //creates a location for each pixel in the m_vArray
    m_vArray.resize(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
    //displays every pixel stored in the m_array
    target.draw(m_vArray);
}


void ComplexPlane::updateRender()
{
    if (m_state == State::CALCULATING)
    {
        // Double for loop, iterates through all pixels
        for (float i = 0; i < m_pixel_size.y; i++)
        {
            for (float j = 0; j < m_pixel_size.x; j++)
            {
                m_vArray[j + i * m_pixel_size.x].position = { j, i };

                //find the Vector2f coordinate
                Vector2f coordinate = mapPixelToCoords(Vector2i(j, i));

                // dteremines the number of iderations for a pixel to ultimately help determine its color
                int iterations = countIterations(coordinate);
                Uint8 r, g, b;
                iterationsToRGB(iterations, r, g, b);

                // Sets the color for the point/vertex/pixel
                m_vArray[j + i * m_pixel_size.x].color = { r, g, b};
            }
        }

    }

    // Set the state to DISPLAYING
    m_state = State::DISPLAYING;
}

//keeps track of each time the user left clicks and zooms in accordingly
void ComplexPlane::zoomIn()
{
    m_ZoomCount++;

    //calculates the new size based on the number of zoom-ins
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);

    //updates the plane with the new dimensions
    m_plane_size = {xSize, ySize};
    m_state = State::CALCULATING;
}

//keeps track of each time the user right clicks and zooms out accordingly
void ComplexPlane::zoomOut()
{
    m_ZoomCount--;

    //everything is pretty much the same except m_ZoomCount being negative will make the exponent negative making width and height multiplied by a fraction which is the same as dividing
    float xSize = BASE_WIDTH * pow(BASE_ZOOM, m_ZoomCount);
    float ySize = BASE_HEIGHT * m_aspectRatio * pow(BASE_ZOOM, m_ZoomCount);
    m_plane_size = {xSize, ySize};
    m_state = State::CALCULATING;
}


void ComplexPlane::setCenter(Vector2i mousePixel)
{
    //sets mousePixel to 0,0
    m_plane_center = mapPixelToCoords(mousePixel);
    m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
    //converts the coordinate of the mouse to a complexPlane coord
    m_mouseLocation = ComplexPlane::mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text& text)
{
    stringstream strm;

    //feeds text into strm
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

    int iterations = 0;

    complex<float> c(coord.x, coord.y);
    complex<float> z;

    //float realTerm = coord.x;
    //float imagTerm = coord.y;
    //float z = 0, c;

    //c = sqrt(pow(realTerm, 2) + pow(imagTerm, 2));

    while (iterations < MAX_ITER)
    {
        z = (z * z) + c;

        if (abs(z) > 2.0)
        {
            return iterations;
        }

        iterations++;
    }

    return MAX_ITER;
}


void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b)
{
    //each of the below sets a different color for a pixel based on its number of iterations
    if (count == MAX_ITER)
    {
        r = 0;
        g = 0;
        b = 0;
    }
    
    //red
    else if (204 <= count && count > 254)
    {
        r = 255;
        g = 0;
        b = 0;
    }

    //yellow
    else if (153 <= count && count > 203)
    {
        r = 255;
        g = 251;
        b = 0;
    }

    //green
    else if (102 <= count && count > 152)
    {
        r = 25;
        g = 194;
        b = 67;
    }

    //turqoiuse
    else if (51 <= count && count > 101)
    {
        r = 0;
        g = 219;
        b = 212;
    }

    //blurple
    else if (0 <= count && count > 50)
    {
        r = 113;
        g = 0;
        b = 219;
    }

}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel) 
{

    float x, y, mX, mY;
    //declared in order of use in equation, also best written as floats as Vector2f holds floats and it keeps things more consistent
    float a, b, c, d;
    
    //in mousPixel they are declard as Vector2i, the i stands for int
    //since the return type is a vector of floats our values need to be converted to floats to have accurate results
    x = static_cast<float>(mousePixel.x);
    y = static_cast<float>(mousePixel.y);

    //set the range
    a = 0;
    //b = static_cast<float>(m.x);
    b = m_pixel_size.x;
    //c = m_plane_center.x - m_plane_size.x / 2.0f;
    //d = 2.0f;
    c = m_plane_center.x - m_plane_size.x / 2.0;

    //maps x coords
    mX = ((x - a) / (b - a)) * m_plane_size.x + c;

    //reset range for y
    a = m_pixel_size.y;
    b = 0;

    //maps y coords
    c = m_plane_center.y - m_plane_size.y / 2.0f;
    mY = ((y - a) / (b - a)) * m_plane_size.y + c;

    //creates a vector with mapped coords
    Vector2f mousePixelF = {mX, mY};

    return mousePixelF;

}
