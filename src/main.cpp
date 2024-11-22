#include <sil/sil.hpp>
#include "random.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <glm/gtx/matrix_transform_2d.hpp>

void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swap_color(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void grayscale(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float luminance{0.2126f * color.r + 0.7152f * color.g + 0.0722f * color.b};
        color.r = luminance;
        color.g = luminance;
        color.b = luminance;
    }
}

void negative(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}

void degrade(sil::Image &image)
{
    float largeur{static_cast<float>(image.width())};
    for (int x{0}; x < image.width(); x++)
    {
        float abscisse{static_cast<float>(x)};
        float pourcentage_abscisse{abscisse / largeur};
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = pourcentage_abscisse;
            image.pixel(x, y).g = pourcentage_abscisse;
            image.pixel(x, y).b = pourcentage_abscisse;
        }
    }
}

void miroir(sil::Image &image)
{
    sil::Image copie{image};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y) = copie.pixel(copie.width() - (x + 1), y);
        }
    }
}

void bruit(sil::Image &image)
{
    for (int a{0}; a < 20000; a++)
    {
        image.pixel(random_int(0, image.width()), random_int(0, image.height())).r = random_float(0, 1);
        image.pixel(random_int(0, image.width()), random_int(0, image.height())).g = random_float(0, 1);
        image.pixel(random_int(0, image.width()), random_int(0, image.height())).b = random_float(0, 1);
    }
}

void rotation_90(sil::Image &image)
{
    sil::Image new_image{image.height(), image.width()};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            new_image.pixel(y, x) = image.pixel(image.width() - (x + 1), y);
        }
    }
    new_image.save("output/ex8.png");
}

void split_rgb(sil::Image &image)
{
    sil::Image new_image{image};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (25 <= x && x < image.width() - 25)
            {
                new_image.pixel(x, y).r = image.pixel(x + 25, y).r;
                new_image.pixel(x, y).g = image.pixel(x, y).g;
                new_image.pixel(x, y).b = image.pixel(x - 25, y).b;
            }
            if (x < 25)
            {
                new_image.pixel(x, y).r = image.pixel(x + 25, y).r;
                new_image.pixel(x, y).g = image.pixel(x, y).g;
            }
            if (image.width() - 25 < x)
            {
                new_image.pixel(x, y).g = image.pixel(x, y).g;
                new_image.pixel(x, y).b = image.pixel(x - 25, y).b;
            }
        }
    }
    new_image.save("output/ex9.png");
}

void eclaircissement(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, 0.5);
        color.g = pow(color.g, 0.5);
        color.b = pow(color.b, 0.5);
    }
}

void assombrissement(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = pow(color.r, 2);
        color.g = pow(color.g, 2);
        color.b = pow(color.b, 2);
    }
}

void disque(sil::Image &image)
{
    int centerX{image.width() / 2};
    int centerY{image.height() / 2};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if (pow((x - centerX), 2) + pow((y - centerY), 2) <= pow(125, 2))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void cercle(float thickness, sil::Image &image)
{
    float centerX{image.width() / 2.f};
    float centerY{image.height() / 2.f};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow((x - centerX), 2) + pow((y - centerY), 2) <= pow(100 + (thickness / 2), 2)) && (pow((x - centerX), 2) + pow((y - centerY), 2) >= pow(100 - (thickness / 2), 2)))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void animation(sil::Image &image)
{
    int centerY{image.height() / 2};
    for (int i{0}; i < 21; i++)
    {
        sil::Image copie{image};
        int centerX{i * (copie.width() / 20)};
        for (int x{0}; x < copie.width(); x++)
        {
            for (int y{0}; y < copie.height(); y++)
            {
                if (pow((x - centerX), 2) + pow((y - centerY), 2) <= pow(125, 2))
                {
                    copie.pixel(x, y).r = 1.f;
                    copie.pixel(x, y).g = 1.f;
                    copie.pixel(x, y).b = 1.f;
                }
            }
        }
        copie.save("output/ex13-" + std::to_string(i) + ".png");
    }
}

void cercle_avec_centre(float thickness, sil::Image &image, float rayon, float centerX, float centerY)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            if ((pow((x - centerX), 2) + pow((y - centerY), 2) <= pow(rayon + (thickness / 2), 2)) && (pow((x - centerX), 2) + pow((y - centerY), 2) >= pow(rayon - (thickness / 2), 2)))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}

void rosace(float thickness, sil::Image &image)
{
    cercle(thickness, image);
    for (float i{0}; i <= (5 * M_PI) / 3; i += M_PI / 3)
    {
        cercle_avec_centre(thickness, image, 100 + thickness / 2, (image.width() / 2) + 100 * cos(i), (image.height() / 2) + 100 * sin(i));
    }
}

void mosaique(int nbr, sil::Image &image)
{
    sil::Image new_image{nbr * image.width(), nbr * image.height()};
    for (int i{0}; i < nbr; i++)
    {
        for (int j{0}; j < nbr; j++)
        {
            for (int x{0}; x < image.width(); x++)
            {
                for (int y{0}; y < image.height(); y++)
                {
                    new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                }
            }
        }
    }
    new_image.save("output/ex15.png");
}

void mosaique_miroir(int nbr, sil::Image &image)
{
    sil::Image new_image{nbr * image.width(), nbr * image.height()};
    for (int j{0}; j < nbr; j++)
        for (int i{0}; i < nbr; i++)
        {
            if (j % 2 == 0)
            {
                if (i % 2 == 0)
                    for (int x{0}; x < image.width(); x++)
                        for (int y{0}; y < image.height(); y++)
                            new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, y);
                if (i % 2 == 1)
                    for (int x{0}; x < image.width(); x++)
                        for (int y{0}; y < image.height(); y++)
                            new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(image.width() - (x + 1), y);
            }
            if (j % 2 == 1)
            {
                if (i % 2 == 0)
                    for (int x{0}; x < image.width(); x++)
                        for (int y{0}; y < image.height(); y++)
                            new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(x, image.height() - (y + 1));
                if (i % 2 == 1)
                    for (int x{0}; x < image.width(); x++)
                        for (int y{0}; y < image.height(); y++)
                            new_image.pixel(x + i * image.width(), y + j * image.height()) = image.pixel(image.width() - (x + 1), image.height() - (y + 1));
            }
        }
    new_image.save("output/ex16.png");
}

void glitch(sil::Image &image)
{
    for (int a{0}; a < 200; a++)
    {
        int longu{random_int(10, 20)};
        int larg{random_int(1, 6)};
        int x_rect1{random_int(0, image.width() - (longu + 1))};
        int y_rect1{random_int(0, image.height() - (larg + 1))};
        int x_rect2{random_int(0, image.width() - (longu + 1))};
        int y_rect2{random_int(0, image.height() - (larg + 1))};
        for (int x{0}; x < longu; x++)
            for (int y{0}; y < larg; y++)
                std::swap(image.pixel(x_rect1 + x, y_rect1 + y), image.pixel(x_rect2 + x, y_rect2 + y));
    }
}

void degrade_couleur1(sil::Image &image)
{
    float largeur{static_cast<float>(image.width())};
    for (int x{0}; x < image.width(); x++)
    {
        float abscisse{static_cast<float>(x)};
        float pourcentage_abscisse{abscisse / largeur};
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 1 - pourcentage_abscisse;
            image.pixel(x, y).g = pourcentage_abscisse;
            image.pixel(x, y).b = 0.f;
        }
    }
}

struct Lab
{
    float L;
    float a;
    float b;
};

float sRGBToLinear(float c)
{
    if (c <= 0.04045)
    {
        return c / 12.92;
    }
    else
    {
        return pow((c + 0.055) / 1.055, 2.4);
    }
}

glm::vec3 convertSRGBToLinearRGB(const glm::vec3 &srgb)
{
    return {
        sRGBToLinear(srgb[0]),
        sRGBToLinear(srgb[1]),
        sRGBToLinear(srgb[2])};
}

float linearToSRGB(float c)
{
    if (c <= 0.0031308)
    {
        return c * 12.92;
    }
    else
    {
        return 1.055 * pow(c, 1.0 / 2.4) - 0.055;
    }
}

glm::vec3 convertLinearRGBToSRGB(const glm::vec3 &linearRGB)
{
    return {
        linearToSRGB(linearRGB[0]),
        linearToSRGB(linearRGB[1]),
        linearToSRGB(linearRGB[2])};
}

Lab srgb_to_oklab(glm::vec3 c)
{
    c = convertSRGBToLinearRGB(c);
    float l = 0.4122214708f * c.r + 0.5363325363f * c.g + 0.0514459929f * c.b;
    float m = 0.2119034982f * c.r + 0.6806995451f * c.g + 0.1073969566f * c.b;
    float s = 0.0883024619f * c.r + 0.2817188376f * c.g + 0.6299787005f * c.b;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    return {
        0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_,
        1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_,
        0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_,
    };
}

glm::vec3 oklab_to_srgb(Lab c)
{
    float l_ = c.L + 0.3963377774f * c.a + 0.2158037573f * c.b;
    float m_ = c.L - 0.1055613458f * c.a - 0.0638541728f * c.b;
    float s_ = c.L - 0.0894841775f * c.a - 1.2914855480f * c.b;

    float l = l_ * l_ * l_;
    float m = m_ * m_ * m_;
    float s = s_ * s_ * s_;

    glm::vec3 b = {
        +4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s,
        -1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s,
        -0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s,
    };
    return {convertLinearRGBToSRGB(b)};
}

void degrade_couleur2(sil::Image &image)
{
    Lab red_en_lab = srgb_to_oklab({1, 0, 0});
    Lab green_en_lab = srgb_to_oklab({0, 1, 0});
    float largeur{static_cast<float>(image.width())};
    for (int x{0}; x < image.width(); x++)
    {
        float abscisse{static_cast<float>(x)};
        float pourcentage_abscisse{abscisse / largeur};
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = red_en_lab.L * (1 - pourcentage_abscisse) + green_en_lab.L * pourcentage_abscisse;
            image.pixel(x, y).g = red_en_lab.a * (1 - pourcentage_abscisse) + green_en_lab.a * pourcentage_abscisse;
            image.pixel(x, y).b = red_en_lab.b * (1 - pourcentage_abscisse) + green_en_lab.b * pourcentage_abscisse;
            image.pixel(x, y) = oklab_to_srgb({image.pixel(x, y).r, image.pixel(x, y).g, image.pixel(x, y).b});
        }
    }
}

void fractale(sil::Image &image)
{
    const float x_min = -2.0f, x_max = 2.0f;
    const float y_min = -2.0f, y_max = 2.0f;
    const int max_iterations = 20;

    for (int px = 0; px < image.width(); ++px)
    {
        for (int py = 0; py < image.height(); ++py)
        {
            float x = x_min + (x_max - x_min) * px / image.width();
            float y = y_min + (y_max - y_min) * py / image.height();

            std::complex<float> c{x, y};
            std::complex<float> z{0.0f, 0.0f};

            int iterations = 0;
            while (iterations < max_iterations && std::abs(z) <= 2.0f)
            {
                z = z * z + c;
                ++iterations;
            }
            float intensity = static_cast<float>(iterations) / max_iterations;
            image.pixel(px, py) = {intensity, intensity, intensity};
        }
    }
}

void normalisation(sil::Image &image)
{
    float min_luminance{1.0f};
    float max_luminance{0.0f};

    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            glm::vec3 pixel = image.pixel(x, y);
            float luminance{0.2126f * pixel.r + 0.7152f * pixel.g + 0.0722f * pixel.b};
            min_luminance = std::min(min_luminance, luminance);
            max_luminance = std::max(max_luminance, luminance);
        }
    }

    for (int y = 0; y < image.height(); ++y)
    {
        for (int x = 0; x < image.width(); ++x)
        {
            glm::vec3 pixel{image.pixel(x, y)};
            glm::vec3 normalized = (pixel - min_luminance) / (max_luminance - min_luminance);
            image.pixel(x, y) =normalized;
        }
    }
}

glm::vec2 rotated(glm::vec2 point, glm::vec2 center_of_rotation, float angle)
{
    return glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{point - center_of_rotation, 0.f}} + center_of_rotation;
}

void vortex(sil::Image &image)
{
    
    sil::Image new_image{image.width(), image.height()};
    float centerX{image.width() / 2};
    float centerY{image.height() / 2};
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float distance_au_centre {glm::distance(glm::vec2{x, y},glm::vec2{centerX, centerY})};
            float angle{0.1 * distance_au_centre + 2*M_PI};

            float new_x{rotated({x, y}, {centerX, centerY}, angle).x};
            float new_y{rotated({x, y}, {centerX, centerY}, angle).y};
            if (new_x > 0 && new_x < image.width() && new_y > 0 && new_y < image.height())
                new_image.pixel(x, y) = image.pixel(new_x, new_y);
            else
            {
                new_image.pixel(x, y) = {0, 0, 0};
            }
        }
    }
    new_image.save("output/ex21.png");
}

int main()
{
    // {
    //     sil::Image image{"images/logo.png"};
    //     keep_green_only(image);
    //     image.save("output/ex1.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     swap_color(image);
    //     image.save("output/ex2.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     grayscale(image);
    //     image.save("output/ex3.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negative(image);
    //     image.save("output/ex4.png");
    // }
    // {
    //     sil::Image image{300 /*width*/, 200 /*height*/};
    //     degrade(image);
    //     image.save("output/ex5.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     miroir(image);
    //     image.save("output/ex6.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     bruit(image);
    //     image.save("output/ex7.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rotation_90(image);
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     split_rgb(image);
    // }
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     eclaircissement(image);
    //     image.save("output/ex10.png");
    // }
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     assombrissement(image);
    //     image.save("output/ex10bis.png");
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     disque(image);
    //     image.save("output/ex11.png");
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     cercle(7, image);
    //     image.save("output/ex12.png");
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     animation(image);
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     rosace(4, image);
    //     image.save("output/ex14.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique(5, image);
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique_miroir(5, image);
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     glitch(image);
    //     image.save("output/ex17.png");
    // }
    // {
    //     sil::Image image{300 /*width*/, 200 /*height*/};
    //     degrade_couleur1(image);
    //     image.save("output/ex18-1.png");
    // }
    // {
    //     sil::Image image{300 /*width*/, 200 /*height*/};
    //     degrade_couleur2(image);
    //     image.save("output/ex18-2.png");
    // }
    // {
    //     sil::Image image{500 /*width*/, 500 /*height*/};
    //     fractale(image);
    //     image.save("output/ex19.png");
    // }
    // {
    //     sil::Image image{"images/photo_faible_contraste.jpg"};
    //     normalisation(image);
    //     image.save("output/ex20.png");
    // }
    {
        sil::Image image{"images/logo.png"};
        vortex(image);
    }
}