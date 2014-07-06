/* INFO ************************************************************************
**                                                                            **
**                                   cutils                                   **
**                                   ======                                   **
**                                                                            **
**                     Modern and Lightweight C Utilities                     **
**                       Version: 0.8.72.026 (20140706)                       **
**                                                                            **
**                                File: ccol.h                                **
**                                                                            **
**           Designed and written by Peter Varo. Copyright (c) 2014           **
**             License agreement is provided in the LICENSE file              **
**                 For more info visit: http://www.cutils.org                 **
**                                                                            **
************************************************************************ INFO */

#ifndef _C_COLOR_H_
#define _C_COLOR_H_

#include <math.h>   // floorf();
#include <stdio.h>  // printf(); sprintf();

/*----------------------------------------------------------------------------*/
// Color types
#undef RGB
#undef RGBA
#undef HSB
#undef HSBA
#undef HSL
#undef HSLA

#define RGB  0
#define RGBA 1
#define HSB  2
#define HSBA 3
#define HSL  4
#define HSLA 5


/*----------------------------------------------------------------------------*/
// RGBA value ranges
#ifndef CCOL_RGBA_R_MIN
  #define CCOL_RGBA_R_MIN 0.f
#endif
#ifndef CCOL_RGBA_R_MAX
  #define CCOL_RGBA_R_MAX 1.f
#endif

#ifndef CCOL_RGBA_G_MIN
  #define CCOL_RGBA_G_MIN 0.f
#endif
#ifndef CCOL_RGBA_G_MAX
  #define CCOL_RGBA_G_MAX 1.f
#endif

#ifndef CCOL_RGBA_B_MIN
  #define CCOL_RGBA_B_MIN 0.f
#endif
#ifndef CCOL_RGBA_B_MAX
  #define CCOL_RGBA_B_MAX 1.f
#endif

#ifndef CCOL_RGBA_A_MIN
  #define CCOL_RGBA_A_MIN 0.f
#endif
#ifndef CCOL_RGBA_A_MAX
  #define CCOL_RGBA_A_MAX 1.f
#endif

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// HSBA value ranges
#ifndef CCOL_HSBA_H_MIN
  #define CCOL_HSBA_H_MIN 0.f
#endif
#ifndef CCOL_HSBA_H_MAX
  #define CCOL_HSBA_H_MAX 1.f
#endif

#ifndef CCOL_HSBA_S_MIN
  #define CCOL_HSBA_S_MIN 0.f
#endif
#ifndef CCOL_HSBA_S_MAX
  #define CCOL_HSBA_S_MAX 1.f
#endif

#ifndef CCOL_HSBA_B_MIN
  #define CCOL_HSBA_B_MIN 0.f
#endif
#ifndef CCOL_HSBA_B_MAX
  #define CCOL_HSBA_B_MAX 1.f
#endif

#ifndef CCOL_HSBA_A_MIN
  #define CCOL_HSBA_A_MIN 0.f
#endif
#ifndef CCOL_HSBA_A_MAX
  #define CCOL_HSBA_A_MAX 1.f
#endif

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
// HSLA value ranges
#ifndef CCOL_HSLA_H_MIN
  #define CCOL_HSLA_H_MIN 0.f
#endif
#ifndef CCOL_HSLA_H_MAX
  #define CCOL_HSLA_H_MAX 1.f
#endif

#ifndef CCOL_HSLA_S_MIN
  #define CCOL_HSLA_S_MIN 0.f
#endif
#ifndef CCOL_HSLA_S_MAX
  #define CCOL_HSLA_S_MAX 1.f
#endif

#ifndef CCOL_HSLA_L_MIN
  #define CCOL_HSLA_L_MIN 0.f
#endif
#ifndef CCOL_HSLA_L_MAX
  #define CCOL_HSLA_L_MAX 1.f
#endif

#ifndef CCOL_HSLA_A_MIN
  #define CCOL_HSLA_A_MIN 0.f
#endif
#ifndef CCOL_HSLA_A_MAX
  #define CCOL_HSLA_A_MAX 1.f
#endif


/*----------------------------------------------------------------------------*/
// Color Base Type
typedef float clr3[3];
typedef float clr4[4];
typedef int hex3[3];
typedef int hex4[4];
typedef const char* hexs;


/*----------------------------------------------------------------------------*/
// Convert functions
static inline void
clr3_to_rgb(int  type,
            clr3 color)
{
    switch (type)
    {
        case RGB: break;
        case HSB: break;
        case HSL: break;
        default: break;
    }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr4_to_rgba(int  type,
             clr4 color)
{
    switch (type)
    {
        case RGBA: break;
        case HSBA: break;
        case HSLA: break;
        default: break;
    }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr3_to_hsb(int  type,
            clr3 color)
{
    switch (type)
    {
        case RGB: break;
        case HSB: break;
        case HSL: break;
        default: break;
    }
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr4_to_hsba(int  type,
             clr4 color)
{
    switch (type)
    {
        case RGBA: break;
        case HSBA: break;
        case HSLA: break;
        default: break;
    }
}


/*----------------------------------------------------------------------------*/
// Blend functions
static inline void
clr3_overlay(int  type_in1,
             clr3 color_in1,
             int  type_in2,
             clr3 color_in2,
             int  type_out,
             clr3 color_out)
{
    return;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr4_overlay(int  type_in1,
             clr4 color_in1,
             int  type_in2,
             clr4 color_in2,
             int  type_out,
             clr4 color_out)
{
    return;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr3_multiply(int  type_in1,
              clr3 color_in1,
              int  type_in2,
              clr3 color_in2,
              int  type_out,
              clr3 color_out)
{
    return;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
clr4_multiply(int  type_in1,
              clr4 color_in1,
              int  type_in2,
              clr4 color_in2,
              int  type_out,
              clr4 color_out)
{
    return;
}


/*----------------------------------------------------------------------------*/
// String converter
static inline void
hexs_to_clr3(hexs string,
             int  type,
             clr3 color)
{
    return;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
hex3_to_clr3(hex3 string,
             int  type,
             clr3 color)
{
    return;
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
hex4_to_clr4(hex4 string,
             int  type,
             clr4 color)
{
    return;
}


/*----------------------------------------------------------------------------*/
// String representations
#define _CCOL_REPR_PREFIX "color("
#define _CCOL_REPR_SUFFIX ")"
#define _CCOL_REPR_FLOAT3 _CCOL_REPR_PREFIX "%f, %f, %f" _CCOL_REPR_SUFFIX
#define _CCOL_REPR_HEXDEC _CCOL_REPR_PREFIX "#%02X%02X%02X" _CCOL_REPR_SUFFIX

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
print_clr3(int type,
           clr3 color)
{
    clr3 clr = {color[0], color[1], color[2]};
    if (type != RGB) clr3_to_rgb(type, clr);
    printf(_CCOL_REPR_FLOAT3 "\n", clr[0], clr[1], clr[2]);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
print_hex3(int type,
           clr3 color)
{
    clr3 clr = {color[0], color[1], color[2]};
    if (type != RGB) clr3_to_rgb(type, clr);
    printf(_CCOL_REPR_HEXDEC "\n",
          (unsigned int)floorf(clr[0] * 255.f),
          (unsigned int)floorf(clr[1] * 255.f),
          (unsigned int)floorf(clr[2] * 255.f));
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
sprint_clr3(char *buffer,
            int type,
            clr3 color)
{
    clr3 clr = {color[0], color[1], color[2]};
    if (type != RGB) clr3_to_rgb(type, clr);
    sprintf(buffer, _CCOL_REPR_FLOAT3, clr[0], clr[1], clr[2]);
}

/*- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
static inline void
sprint_hex3(char *buffer,
            int type,
            clr3 color)
{
    clr3 clr = {color[0], color[1], color[2]};
    if (type != RGB) clr3_to_rgb(type, clr);
    sprintf(buffer,
            _CCOL_REPR_HEXDEC,
            (unsigned int)floorf(clr[0] * 255.f),
            (unsigned int)floorf(clr[1] * 255.f),
            (unsigned int)floorf(clr[2] * 255.f));
}


/*----------------------------------------------------------------------------*/
// Constant color macros
#undef  _CCOL_CONST
#define _CCOL_CONST(r, g, b) {(CCOL_RGBA_R_MAX - CCOL_RGBA_R_MIN)*r, \
                              (CCOL_RGBA_G_MAX - CCOL_RGBA_G_MIN)*g, \
                              (CCOL_RGBA_B_MAX - CCOL_RGBA_B_MIN)*b}

#define BLACK {CCOL_RGBA_R_MIN, CCOL_RGBA_G_MIN, CCOL_RGBA_B_MIN}
#define WHITE {CCOL_RGBA_R_MAX, CCOL_RGBA_G_MAX, CCOL_RGBA_B_MAX}

// X11 Color Names {http://en.wikipedia.org/wiki/X11_color_names}
#define ALICEBLUE            _CCOL_CONST( 0.9411764705882353,  0.9725490196078431,                  1.0)
#define ANTIQUEWHITE         _CCOL_CONST( 0.9803921568627451,  0.9215686274509803,   0.8431372549019608)
#define AQUA                 _CCOL_CONST(                0.0,                 1.0,                  1.0)
#define AQUAMARINE           _CCOL_CONST( 0.4980392156862745,                 1.0,   0.8313725490196079)
#define AZURE                _CCOL_CONST( 0.9411764705882353,                 1.0,                  1.0)
#define BEIGE                _CCOL_CONST( 0.9607843137254902,  0.9607843137254902,   0.8627450980392157)
#define BISQUE               _CCOL_CONST(                1.0,  0.8941176470588236,   0.7686274509803922)
#define BLANCHEDALMOND       _CCOL_CONST(                1.0,  0.9215686274509803,    0.803921568627451)
#define BLUE                 _CCOL_CONST(                0.0,                 0.0,                  1.0)
#define BLUEVIOLET           _CCOL_CONST( 0.5411764705882353, 0.16862745098039217,   0.8862745098039215)
#define BROWN                _CCOL_CONST( 0.6470588235294118, 0.16470588235294117,  0.16470588235294117)
#define BURLYWOOD            _CCOL_CONST( 0.8705882352941177,  0.7215686274509804,   0.5294117647058824)
#define CADETBLUE            _CCOL_CONST(0.37254901960784315,  0.6196078431372549,   0.6274509803921569)
#define CHARTREUSE           _CCOL_CONST( 0.4980392156862745,                 1.0,                  0.0)
#define CHOCOLATE            _CCOL_CONST( 0.8235294117647058,  0.4117647058823529,  0.11764705882352941)
#define CORAL                _CCOL_CONST(                1.0,  0.4980392156862745,   0.3137254901960784)
#define CORNFLOWERBLUE       _CCOL_CONST(0.39215686274509803,  0.5843137254901961,   0.9294117647058824)
#define CORNSILK             _CCOL_CONST(                1.0,  0.9725490196078431,   0.8627450980392157)
#define CRIMSON              _CCOL_CONST( 0.8627450980392157,  0.0784313725490196,  0.23529411764705882)
#define CYAN                 _CCOL_CONST(                0.0,                 1.0,                  1.0)
#define DARKBLUE             _CCOL_CONST(                0.0,                 0.0,   0.5450980392156862)
#define DARKCYAN             _CCOL_CONST(                0.0,  0.5450980392156862,   0.5450980392156862)
#define DARKGOLDENROD        _CCOL_CONST( 0.7215686274509804,  0.5254901960784314, 0.043137254901960784)
#define DARKGRAY             _CCOL_CONST( 0.6627450980392157,  0.6627450980392157,   0.6627450980392157)
#define DARKGREEN            _CCOL_CONST(                0.0, 0.39215686274509803,                  0.0)
#define DARKKHAKI            _CCOL_CONST( 0.7411764705882353,  0.7176470588235294,   0.4196078431372549)
#define DARKMAGENTA          _CCOL_CONST( 0.5450980392156862,                 0.0,   0.5450980392156862)
#define DARKOLIVEGREEN       _CCOL_CONST( 0.3333333333333333,  0.4196078431372549,   0.1843137254901961)
#define DARKORANGE           _CCOL_CONST(                1.0,  0.5490196078431373,                  0.0)
#define DARKORCHID           _CCOL_CONST(                0.6, 0.19607843137254902,                  0.8)
#define DARKRED              _CCOL_CONST( 0.5450980392156862,                 0.0,                  0.0)
#define DARKSALMON           _CCOL_CONST( 0.9137254901960784,  0.5882352941176471,  0.47843137254901963)
#define DARKSEAGREEN         _CCOL_CONST( 0.5607843137254902,  0.7372549019607844,   0.5607843137254902)
#define DARKSLATEBLUE        _CCOL_CONST( 0.2823529411764706, 0.23921568627450981,   0.5450980392156862)
#define DARKSLATEGRAY        _CCOL_CONST( 0.1843137254901961, 0.30980392156862746,  0.30980392156862746)
#define DARKTURQUOISE        _CCOL_CONST(                0.0,   0.807843137254902,   0.8196078431372549)
#define DARKVIOLET           _CCOL_CONST( 0.5803921568627451,                 0.0,   0.8274509803921568)
#define DEEPPINK             _CCOL_CONST(                1.0,  0.0784313725490196,   0.5764705882352941)
#define DEEPSKYBLUE          _CCOL_CONST(                0.0,  0.7490196078431373,                  1.0)
#define DIMGRAY              _CCOL_CONST( 0.4117647058823529,  0.4117647058823529,   0.4117647058823529)
#define DODGERBLUE           _CCOL_CONST(0.11764705882352941,  0.5647058823529412,                  1.0)
#define FIREBRICK            _CCOL_CONST( 0.6980392156862745, 0.13333333333333333,  0.13333333333333333)
#define FLORALWHITE          _CCOL_CONST(                1.0,  0.9803921568627451,   0.9411764705882353)
#define FORESTGREEN          _CCOL_CONST(0.13333333333333333,  0.5450980392156862,  0.13333333333333333)
#define FUCHSIA              _CCOL_CONST(                1.0,                 0.0,                  1.0)
#define GAINSBORO            _CCOL_CONST( 0.8627450980392157,  0.8627450980392157,   0.8627450980392157)
#define GHOSTWHITE           _CCOL_CONST( 0.9725490196078431,  0.9725490196078431,                  1.0)
#define GOLD                 _CCOL_CONST(                1.0,  0.8431372549019608,                  0.0)
#define GOLDENROD            _CCOL_CONST( 0.8549019607843137,  0.6470588235294118,  0.12549019607843137)
#define GRAY                 _CCOL_CONST( 0.5019607843137255,  0.5019607843137255,   0.5019607843137255)
#define GREEN                _CCOL_CONST(                0.0,  0.5019607843137255,                  0.0)
#define GREENYELLOW          _CCOL_CONST( 0.6784313725490196,                 1.0,   0.1843137254901961)
#define HONEYDEW             _CCOL_CONST( 0.9411764705882353,                 1.0,   0.9411764705882353)
#define HOTPINK              _CCOL_CONST(                1.0,  0.4117647058823529,   0.7058823529411765)
#define INDIANRED            _CCOL_CONST(  0.803921568627451,  0.3607843137254902,   0.3607843137254902)
#define INDIGO               _CCOL_CONST(0.29411764705882354,                 0.0,   0.5098039215686274)
#define IVORY                _CCOL_CONST(                1.0,                 1.0,   0.9411764705882353)
#define KHAKI                _CCOL_CONST( 0.9411764705882353,  0.9019607843137255,   0.5490196078431373)
#define LAVENDER             _CCOL_CONST( 0.9019607843137255,  0.9019607843137255,   0.9803921568627451)
#define LAVENDERBLUSH        _CCOL_CONST(                1.0,  0.9411764705882353,   0.9607843137254902)
#define LAWNGREEN            _CCOL_CONST(0.48627450980392156,  0.9882352941176471,                  0.0)
#define LEMONCHIFFON         _CCOL_CONST(                1.0,  0.9803921568627451,    0.803921568627451)
#define LIGHTBLUE            _CCOL_CONST( 0.6784313725490196,  0.8470588235294118,   0.9019607843137255)
#define LIGHTCORAL           _CCOL_CONST( 0.9411764705882353,  0.5019607843137255,   0.5019607843137255)
#define LIGHTCYAN            _CCOL_CONST( 0.8784313725490196,                 1.0,                  1.0)
#define LIGHTGOLDENRODYELLOW _CCOL_CONST( 0.9803921568627451,  0.9803921568627451,   0.8235294117647058)
#define LIGHTGRAY            _CCOL_CONST( 0.8274509803921568,  0.8274509803921568,   0.8274509803921568)
#define LIGHTGREEN           _CCOL_CONST( 0.5647058823529412,  0.9333333333333333,   0.5647058823529412)
#define LIGHTPINK            _CCOL_CONST(                1.0,  0.7137254901960784,   0.7568627450980392)
#define LIGHTSALMON          _CCOL_CONST(                1.0,  0.6274509803921569,  0.47843137254901963)
#define LIGHTSEAGREEN        _CCOL_CONST(0.12549019607843137,  0.6980392156862745,   0.6666666666666666)
#define LIGHTSKYBLUE         _CCOL_CONST( 0.5294117647058824,   0.807843137254902,   0.9803921568627451)
#define LIGHTSLATEGRAY       _CCOL_CONST( 0.4666666666666667,  0.5333333333333333,                  0.6)
#define LIGHTSTEELBLUE       _CCOL_CONST( 0.6901960784313725,  0.7686274509803922,   0.8705882352941177)
#define LIGHTYELLOW          _CCOL_CONST(                1.0,                 1.0,   0.8784313725490196)
#define LIME                 _CCOL_CONST(                0.0,                 1.0,                  0.0)
#define LIMEGREEN            _CCOL_CONST(0.19607843137254902,   0.803921568627451,  0.19607843137254902)
#define LINEN                _CCOL_CONST( 0.9803921568627451,  0.9411764705882353,   0.9019607843137255)
#define MAGENTA              _CCOL_CONST(                1.0,                 0.0,                  1.0)
#define MAROON               _CCOL_CONST( 0.5019607843137255,                 0.0,                  0.0)
#define MEDIUMAQUAMARINE     _CCOL_CONST(                0.4,   0.803921568627451,   0.6666666666666666)
#define MEDIUMBLUE           _CCOL_CONST(                0.0,                 0.0,    0.803921568627451)
#define MEDIUMORCHID         _CCOL_CONST( 0.7294117647058823,  0.3333333333333333,   0.8274509803921568)
#define MEDIUMPURPLE         _CCOL_CONST( 0.5764705882352941,  0.4392156862745098,   0.8588235294117647)
#define MEDIUMSEAGREEN       _CCOL_CONST(0.23529411764705882,  0.7019607843137254,  0.44313725490196076)
#define MEDIUMSLATEBLUE      _CCOL_CONST( 0.4823529411764706, 0.40784313725490196,   0.9333333333333333)
#define MEDIUMSPRINGGREEN    _CCOL_CONST(                0.0,  0.9803921568627451,   0.6039215686274509)
#define MEDIUMTURQUOISE      _CCOL_CONST( 0.2823529411764706,  0.8196078431372549,                  0.8)
#define MEDIUMVIOLETRED      _CCOL_CONST( 0.7803921568627451, 0.08235294117647059,   0.5215686274509804)
#define MIDNIGHTBLUE         _CCOL_CONST(0.09803921568627451, 0.09803921568627451,   0.4392156862745098)
#define MINTCREAM            _CCOL_CONST( 0.9607843137254902,                 1.0,   0.9803921568627451)
#define MISTYROSE            _CCOL_CONST(                1.0,  0.8941176470588236,   0.8823529411764706)
#define MOCCASIN             _CCOL_CONST(                1.0,  0.8941176470588236,   0.7098039215686275)
#define NAVAJOWHITE          _CCOL_CONST(                1.0,  0.8705882352941177,   0.6784313725490196)
#define NAVY                 _CCOL_CONST(                0.0,                 0.0,   0.5019607843137255)
#define OLDLACE              _CCOL_CONST( 0.9921568627450981,  0.9607843137254902,   0.9019607843137255)
#define OLIVE                _CCOL_CONST( 0.5019607843137255,  0.5019607843137255,                  0.0)
#define OLIVEDRAB            _CCOL_CONST( 0.4196078431372549,  0.5568627450980392,  0.13725490196078433)
#define ORANGE               _CCOL_CONST(                1.0,  0.6470588235294118,                  0.0)
#define ORANGERED            _CCOL_CONST(                1.0, 0.27058823529411763,                  0.0)
#define ORCHID               _CCOL_CONST( 0.8549019607843137,  0.4392156862745098,   0.8392156862745098)
#define PALEGOLDENROD        _CCOL_CONST( 0.9333333333333333,  0.9098039215686274,   0.6666666666666666)
#define PALEGREEN            _CCOL_CONST(  0.596078431372549,   0.984313725490196,    0.596078431372549)
#define PALETURQUOISE        _CCOL_CONST( 0.6862745098039216,  0.9333333333333333,   0.9333333333333333)
#define PALEVIOLETRED        _CCOL_CONST( 0.8588235294117647,  0.4392156862745098,   0.5764705882352941)
#define PAPAYAWHIP           _CCOL_CONST(                1.0,  0.9372549019607843,   0.8352941176470589)
#define PEACHPUFF            _CCOL_CONST(                1.0,  0.8549019607843137,   0.7254901960784313)
#define PERU                 _CCOL_CONST(  0.803921568627451,  0.5215686274509804,  0.24705882352941178)
#define PINK                 _CCOL_CONST(                1.0,  0.7529411764705882,    0.796078431372549)
#define PLUM                 _CCOL_CONST( 0.8666666666666667,  0.6274509803921569,   0.8666666666666667)
#define POWDERBLUE           _CCOL_CONST( 0.6901960784313725,  0.8784313725490196,   0.9019607843137255)
#define PURPLE               _CCOL_CONST( 0.5019607843137255,                 0.0,   0.5019607843137255)
#define RED                  _CCOL_CONST(                1.0,                 0.0,                  0.0)
#define ROSYBROWN            _CCOL_CONST( 0.7372549019607844,  0.5607843137254902,   0.5607843137254902)
#define ROYALBLUE            _CCOL_CONST( 0.2549019607843137,  0.4117647058823529,   0.8823529411764706)
#define SADDLEBROWN          _CCOL_CONST( 0.5450980392156862, 0.27058823529411763,  0.07450980392156863)
#define SALMON               _CCOL_CONST( 0.9803921568627451,  0.5019607843137255,   0.4470588235294118)
#define SANDYBROWN           _CCOL_CONST( 0.9568627450980393,  0.6431372549019608,   0.3764705882352941)
#define SEAGREEN             _CCOL_CONST( 0.1803921568627451,  0.5450980392156862,   0.3411764705882353)
#define SEASHELL             _CCOL_CONST(                1.0,  0.9607843137254902,   0.9333333333333333)
#define SIENNA               _CCOL_CONST( 0.6274509803921569,  0.3215686274509804,  0.17647058823529413)
#define SILVER               _CCOL_CONST( 0.7529411764705882,  0.7529411764705882,   0.7529411764705882)
#define SKYBLUE              _CCOL_CONST( 0.5294117647058824,   0.807843137254902,   0.9215686274509803)
#define SLATEBLUE            _CCOL_CONST(0.41568627450980394, 0.35294117647058826,    0.803921568627451)
#define SLATEGRAY            _CCOL_CONST( 0.4392156862745098,  0.5019607843137255,   0.5647058823529412)
#define SNOW                 _CCOL_CONST(                1.0,  0.9803921568627451,   0.9803921568627451)
#define SPRINGGREEN          _CCOL_CONST(                0.0,                 1.0,   0.4980392156862745)
#define STEELBLUE            _CCOL_CONST(0.27450980392156865,  0.5098039215686274,   0.7058823529411765)
#define TAN                  _CCOL_CONST( 0.8235294117647058,  0.7058823529411765,   0.5490196078431373)
#define TEAL                 _CCOL_CONST(                0.0,  0.5019607843137255,   0.5019607843137255)
#define THISTLE              _CCOL_CONST( 0.8470588235294118,  0.7490196078431373,   0.8470588235294118)
#define TOMATO               _CCOL_CONST(                1.0, 0.38823529411764707,   0.2784313725490196)
#define TURQUOISE            _CCOL_CONST(0.25098039215686274,  0.8784313725490196,   0.8156862745098039)
#define VIOLET               _CCOL_CONST( 0.9333333333333333,  0.5098039215686274,   0.9333333333333333)
#define WHEAT                _CCOL_CONST( 0.9607843137254902,  0.8705882352941177,   0.7019607843137254)
#define WHITESMOKE           _CCOL_CONST( 0.9607843137254902,  0.9607843137254902,   0.9607843137254902)
#define YELLOW               _CCOL_CONST(                1.0,                 1.0,                  0.0)
#define YELLOWGREEN          _CCOL_CONST( 0.6039215686274509,   0.803921568627451,  0.19607843137254902)

#endif // _C_COLOR_H_
