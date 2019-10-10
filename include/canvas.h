#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
using std::vector;
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <iomanip>

#include "common.h"

namespace life {

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
            typedef unsigned char component_t; //!< Type of a color channel.
            static constexpr int image_depth=4; //!< Default value is RGBA (4 channels).

        public:

            //=== Special members
            /// Constructor
            /*! Creates an empty canvas of the requested size.
             * @param w_ The canvas width in pixels.
             * @param h_ The canvas height in pixels.
             */
            Canvas( size_t w=0, size_t h=0, short bs=4 )
                : m_width{w*bs}, m_height{h*bs}, m_block_size{ bs }
            {
                // Remember to adjust the virtual size to real dimensions.
                m_pixels.resize( m_width * m_height * image_depth );
            }

            /// Destructor.
            virtual ~Canvas( void )
            {
                // Do nothing, RAII (resource acquisition is resource initialization) approach
            }

            //=== Special members
            /// Copy constructor.
            /*!
             * Deep copy of the canvas.
             * @param clone The object we are copying from.
             */
            Canvas( const Canvas & );
            /// Assignment operator.
            /*!
             * @param source The object we are copying information from.
             * @return A reference to the `this` object.
             */
            Canvas & operator=( const Canvas & );
            /// Move constructor.
            /*!
             * @param clone The object we are move-constructing from.
             */
            Canvas( Canvas && clone );
            /// Move assignment operator.
            /*!
             * @param source The object we are move-assigning from.
             */
            Canvas & operator=( Canvas && );

            //=== Members
            /// Clear the canvas with black color.
            /*!
             * @param The color we assign to all pixels.
             */
            void clear( const Color& = BLACK );
            /// Set the color of a pixel on the canvas.
            /*!
             * Assign a color to a pixel on the virtual image at the requested coordinate.
             *
             * @note Nothing is done if the  pixel coordinate is located outside the canvas.
             * @param p The 2D (virtual) coordinate of the pixel we want to change the color.
             * @param c The color.
             */
            void pixel( const Point2&,  const Color& );

            /// Get the pixel color from the canvas.
            /*!
             * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
             * @param p The 2D (virtual) coordinate of the pixel we want to know the color of.
             * @return The pixel color.
             */
            Color pixel( const Point2& ) const;

            //=== Attribute accessors members.
            /// Return the canvas width.
            size_t width( void ) const
            { return m_width; }
            /// Return the canvas height.
            size_t height( void ) const
            { return m_height; }
            /// Return the canvas pixels, as an unidimensional array of `unsigned char`.
            const component_t* pixels( void ) const
            { return m_pixels.data(); }

        private:
            size_t m_width;    //!< The image width in pixel units.
            size_t m_height;   //!< The image height in pixel units.
            short m_block_size; //!< The virtual pixel size in pixels
            // TODO: If you wish to use a 3D matrix instead of an array, this is where
            // you should replace the vector with the 3D matrix.
            vector< component_t > m_pixels; //!< The pixels, stored as 4 RGBA components.
    };
} // namespace

#endif // CANVAS_H
