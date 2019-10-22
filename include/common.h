#ifndef COMMON_H
#define COMMON_H

#include <cstring> // memset, memcpy
#include <iostream>
#include <map>

namespace life {
   /// Represents a Pixel coordinate defined by `(x,y)`.
   struct Point2
   {
       typedef long coord_type; //!< The cell coordinate type.
       coord_type x; //!< X coordinate of a point.
       coord_type y; //!< Y coordinate of a point.
       /// Creates a point 2d.
       Point2( coord_type x=0, coord_type y=0 ) : x{x}, y{y} {/*empty*/}
       /// Copy constructor
       Point2( const Point2& clone ) : x{ clone.x }, y{ clone.y } {/*empty*/}
       /// Equality comparison.
       bool operator==( const Point2& rhs ) const
       { return x==rhs.x and y==rhs.y ; }
       /// Difference comparison.
       bool operator!=( const Point2& rhs ) const
       { return not operator==( rhs ) ; }
       /// Pre decrement the point, as in `--p`.
       Point2 operator--()
       {
           --x; --y;
           return *this;
       }
       /// Post decrement the point, as in `p--`.
       Point2 operator--(int)
       {
           Point2 temp(*this);
           x--; y--;
           return temp;
       }
       /// Stream extractor
       friend std::ostream& operator<<( std::ostream& os, const Point2& p )
       {
           os << "(x="<< p.x << ", y=" << p.y << ")";
           return os;
       }
   };

   /// Represents a Matrix coordinate, defined as (row, column)
   struct Location2
   {
       typedef long coord_type; //!< The cell coordinate type.
       coord_type r; //!< row coordinate of a location.
       coord_type c; //!< column coordinate of a location.
       /// Creates a 2D location.
       Location2( coord_type r=0, coord_type c=0 ) : r{r}, c{c} {/*empty*/}
       /// Copy constructor
       Location2( const Location2& clone ) : r{ clone.r }, c{ clone.c } {/*empty*/}
       /// Equality comparison.
       bool operator==( const Location2& rhs ) const
       { return r==rhs.r and c==rhs.c ; }
       /// Difference comparison.
       bool operator!=( const Location2& rhs ) const
       { return not operator==( rhs ) ; }
       bool operator<( const Location2& rhs ) const
       { return (r < rhs.r or ( r == rhs.r and c < rhs.c ) ); }
       /// Pre decrement the location.
       Location2 operator--()
       {
           --r; --c;
           return *this;
       }
       /// Post decrement the location.
       Location2 operator--(int)
       {
           Location2 temp(*this);
           r--; c--;
           return temp;
       }
       /// Stream extractor
       friend std::ostream& operator<<( std::ostream& os, const Location2& l )
       {
           os << "(row="<< l.r << ", col=" << l.c << ")";

           return os;
       }
   };

   /// Convert location to point
   inline Point2 Location2Point( const Location2 &l )
   { return Point2{ l.c, l.r }; }

   /// Convert point to location.
   inline Location2 Point2Location( const Point2 &p )
   { return Location2{ p.y, p.x }; }

   /// Represents a Color as a RGB entity.
   struct Color
   {
       //=== Alias
       typedef unsigned char color_t; //!< Type of a color channel.
       /// Identifies each color channel.
       enum channel_e : color_t { R=0, //!< Red channel.
                                  G=1, //!< Green channel.
                                  B=2, //!< Blue channel
                                  A=3  //!< Alpha channel
       };  

       /// the color depth
       static constexpr short N_CHANNELS = 4;

       //=== Members
       color_t channels[N_CHANNELS]; //!< Stores each of the color channels, R, G, and B.
       //=== Methods
       /// Creates a color.
       Color(color_t r=0, color_t g=0, color_t b=0, color_t a=0) : channels{r,g,b,a} {/*empty*/}

       /// Copy constructor.
       Color( const Color& clone )
       {
           std::memcpy( channels, clone.channels, sizeof(color_t)*N_CHANNELS );
       }

       /// Assignment operator.
       Color& operator = ( const Color& rhs )
       {
           if ( &rhs != this )
               std::memcpy( channels, rhs.channels, sizeof(color_t)*N_CHANNELS );
           return *this;
       }

       /// Comparison operator.
       bool operator == ( const Color& rhs )
       {
           return not std::memcmp( channels, rhs.channels, sizeof(color_t)*N_CHANNELS );
       }
       
       friend std::ostream& operator<<( std::ostream& os, const Color& c )
       {
           os << "(" << (int)c.channels[R] << ","
                     << (int)c.channels[G] << ","
                     << (int)c.channels[B] << ","
                     << (int)c.channels[A] << ")";
           return os;
       }
   };

   // A basic color pallete.
   static const Color BLACK         = Color{0,0,0, 255}      ; //!< Black.
   static const Color WHITE         = Color{255,255,255, 255}; //!< White.
   static const Color DARK_GREEN    = Color{0,100,0, 255}    ; //!< Dark green.
   static const Color GREEN         = Color{0,250,0, 255}    ; //!< Green.
   static const Color RED           = Color{255,0,0, 255}    ; //!< Red.
   static const Color BLUE          = Color{0,0,255, 255}    ; //!< Blue.
   static const Color CRIMSON       = Color{220,20,60, 255}  ; //!< Crimson (kind of red).
   static const Color LIGHT_BLUE    = Color{135,206,250, 255}; //!< Light blue.
   static const Color LIGHT_GREY    = Color{210,210,210, 255}; //!< Light blue.
   static const Color DEEP_SKY_BLUE = Color{0,191,255, 255}  ; //!< Deep blue.
   static const Color DODGER_BLUE   = Color{30,144,255, 255} ; //!< Another bluish color.
   static const Color STEEL_BLUE    = Color{70,130,180, 255} ; //!< Yet another bluish color.
   static const Color YELLOW        = Color{255,255,0, 255}  ; //!< Yellow.
   static const Color LIGHT_YELLOW  = Color{255,255,153, 255}; //!< Light yellow.

   /// A color palette for later use.
   static std::map< std::string, Color > color_pallet{
       {  "black",         BLACK },
       {  "white",         WHITE },
       {  "dark green",    DARK_GREEN },
       {  "red",           RED },
       {  "green",         GREEN },
       {  "blue",          BLUE },
       {  "crimson",       CRIMSON },
       {  "light blue",    LIGHT_BLUE },
       {  "light grey",    LIGHT_GREY },
       {  "deep sky blue", DEEP_SKY_BLUE },
       {  "dodger blue",   DODGER_BLUE },
       {  "steel blue",    STEEL_BLUE },
       {  "yellow",        YELLOW },
       {  "light yellow",  LIGHT_YELLOW }
   };

} // namespace

#endif // COMMON_H
