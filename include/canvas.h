#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
using std::vector;
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "common.h"
#include "lodepng.h"

namespace life
{

//! Provides methods for drawing on an image.
/*!
     * This is a drawing area on which we shall draw a Life representation.
     *
     * Here some information on the canvas properties:
     *
     * 1. The drawing area has the origin set to the bottom left corner, with
     * positive `X` axis going to the right and positive `Y` axis going to
     * the top of the canvas.
     * 2. A pixel on the canvas has a square shape based on the pixel size
     * set when the canvas is instantiated.
     * 3. Because of 2, we have the `virtual` dimension (set by the client), 
     * and the `real` dimension, which is w * pixel_size by h * pixel_size.
     *
     * This class returns to the client an image (object) representation of the maze,
     * which might be recorded by the client as a PNG image file.
     */
class Canvas
{

public:
    //=== Alias
    typedef unsigned char component_t;    //!< Type of a color channel.
    static constexpr int image_depth = 4; //!< Default value is RGBA (4 channels).

private:
    size_t m_col;       //!< The image width in pixel units.
    size_t m_row;       //!< The image height in pixel units.
    long total_size{0};
    short m_block_size; //!< The virtual pixel size in pixels
    // TODO: If you wish to use a 3D matrix instead of an array, this is where
    // you should replace the vector with the 3D matrix.
    vector<vector<life::Color>> m_pixels; //!< The pixels, stored as 4 RGBA components.
    //movi para dentro da funcao
    vector<component_t> m_pixel_unidimensional;

public:
    //=== Special members
    /// Constructor
    /*! Creates an empty canvas of the requested size.
             * @param w_ The canvas width in pixels.
             * @param h_ The canvas height in pixels.
             */
    Canvas(size_t col = 0, size_t row = 0, short bs = 4)
        : m_row{row * bs}, m_col{col * bs}, m_block_size{bs}
    {
        // Remember to adjust the virtual size to real dimensions.
        // std::cout << "m_col * m_row = " << m_col * m_row * m_block_size<< std::endl;
        m_pixels.resize(m_row);
        for (int i = 0; i < m_row; i++)
        {
            m_pixels[i].resize(m_col);
        }
        total_size = m_row * m_col * 4;
    }

    /// Destructor.
    ~Canvas(void)
    {
    }

    //=== Special members
    /// Copy constructor.
    /*!
             * Deep copy of the canvas.
             * @param clone The object we are copying from.
             */
    Canvas(const Canvas &);
    /// Assignment operator.
    /*!
             * @param source The object we are copying information from.
             * @return A reference to the `this` object.
             */
    Canvas &operator=(const Canvas &);
    /// Move constructor.
    /*!
             * @param clone The object we are move-constructing from.
             */
    Canvas(Canvas &&clone);
    /// Move assignment operator.
    /*!
             * @param source The object we are move-assigning from.
             */
    Canvas &operator=(Canvas &&);

    //=== Members
    /// Clear the canvas with black color.
    /*!
             * @param The color we assign to all pixels.
             */
    void clear(const Color& choosed_color = GREEN)
    {
        for (int i = 0; i < m_row; ++i)
        {
            for (int j = 0; j < m_col; ++j)
            {
                for (int k = 0; k < 4; k++)
                {
                    m_pixels[i][j].channels[k] = choosed_color.channels[k];
                }
            }
        }
    };
    /// Set the color of a pixel on the canvas.
    /*!
             * Assign a color to a pixel on the virtual image at the requested coordinate.
             *
             * @note Nothing is done if the  pixel coordinate is located outside the canvas.
             * @param p The 2D (virtual) coordinate of the pixel we want to change the color.
             * @param c The color.
             */
    void pixel(const Point2& point, const Color & choosed_color){
        Point2 n_point = convert_pixel(point);

        for (int i = n_point.x; i < n_point.x + m_block_size; i++){
            for (int j = n_point.y; j < n_point.y + m_block_size; j++){
                for (int k = 0; k < 4; k++)
                {
                    m_pixels[i][j].channels[k] = choosed_color.channels[k];
                }
            }
        }   
    };

    /// Get the pixel color from the canvas.
    /*!
             * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
             * @param p The 2D (virtual) coordinate of the pixel we want to know the color of.
             * @return The pixel color.
             */
    Color pixel(const Point2 & point) {
        Point2 n_point = convert_pixel(point);
    };

    //=== Attribute accessors members.
    /// Return the canvas width.

    //remove this comment
    size_t col(void) const
    {
        return m_col;
    }
    /// Return the canvas height.
    size_t row(void) const
    {
        return m_row;
    }
    
    /// Return the canvas pixels, as an unidimensional array of `unsigned char`.
    const component_t* pixels( void )
    { 
        int count{0};
        int progress{0};
        // vector<component_t> m_pixel_unidimensional;
        

        for(int i = 0; i < m_row; i++){
            for(int j = 0; j < m_col; j++){
                for (int k = 0; k < 4; k++)
                {
                    // std::cout << "\runidimensional = " << count++;
                    progress_bar(count++);
                    m_pixel_unidimensional.push_back(m_pixels[i][j].channels[k]);
                }
            }
        }
        return m_pixel_unidimensional.data(); 
    }

    //!< Create progress bar based on input value
    template <typename T>
    void progress_bar(T value){
        long x = ((value+1) * 100)/total_size;
        
        if(value == 0){
            std::cout<<"----------------Creating ppm file------------------\n";
        }
        std::cout.flush();
        std::cout << "[";
        for(int i = 0; i < 50; i++){
            if(i < (x/2) ){
                std::cout <<"*";
            }else{
                std::cout << " ";
            }
        }
        std::cout << "] " << x << "%\r";
        std::cout.flush();

        if(x == 100){
            std::cout<<"\nSaving ppm image...\n";
        }
    }

    const size_t get_size()
    { 
        return total_size; 
    }

    void print(){
        for (int i = 0; i < m_row; ++i)
        {
            std::cout << "line: " << i << std::endl;
            for (int j = 0; j < m_col; ++j)
            {
                std::cout << "{"; 
                for (int k = 0; k < 4; k++)
                {
                    std::cout << (int) m_pixels[i][j].channels[k] << " ";
                }
                std::cout << "} "; 
            }
            std::cout << std::endl;
        }
    }

    //!> Return new points
    Point2 convert_pixel(const Point2& point){
        Point2 n_point;
        
        //change origin from left top to left bottom
        // n_point.x = (m_row / m_block_size) - 1 - point.x;

        n_point.x = point.x * m_block_size;
        n_point.y = point.y * m_block_size;

        return n_point;
    }
};

void encode_png(const char* filename, const unsigned char * image, unsigned width, unsigned height)
{
    
    //Encode the image
    unsigned error = lodepng::encode(filename, image, width, height);

    //if there's an error, display it
    if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

} // namespace life

#endif // CANVAS_H
