/*
BSD 3-Clause License

Copyright (c) 2018, eelcoder
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
         SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __PANDORA_FILTER_GAUSSIAN_NAIVE_H__
#define __PANDORA_FILTER_GAUSSIAN_NAIVE_H__

#include <pandora/image.h>
#include <cmath>

namespace pandora
{
	namespace filter
	{
        namespace details
        {
           /**
            * \brief Apply a Gaussian filter on a grayscale image.
            *        Naive implementation of the Gaussian filter.
            *
            * \remark for more info, see https://eelcoder.wordpress.com.
            */
            class gaussian_naive_impl
            {

            public:

                /**
                * \brief constructor.
                *
                * \param[in] kernel diameter.
                * \param[in] gaussian sigma.
                */
                inline gaussian_naive_impl(int kernel_size,float sigma):
                    kernel_radius(kernel_size/2),sigma_squared(sigma*sigma)
                {
                }
                
                /**
                * \brief apply a gaussian filter on a grayscale image.
                *
                * \param[in] input image.
                * \param[out] output image.
                */
                void apply(const pandora::image8u &input_image, pandora::image8u &output_image)
                {
                    //apply the gaussian filter
                    for (auto y = 0; y < input_image.height(); ++y)
                    {
                        for (auto x = 0; x < input_image.width(); ++x)
                        {
                            //2d convolution using the discrete Gaussian kernel
                            output_image(x,y) = convolve(input_image,x,y);
                        }
                    }
                }

            private:
                
                /**
                 * \brief apply a convolution centered on a pixel.
                 *        2D discrete Gaussian : G(x,y,sigma) = exp(- (x2+y2)/ 2 x sigma2)
                 *
                 * \param[in] input image.
                 * \param[in] x coordinate of the pixel to process.
                 * \param[in] y coordinate of the pixel to process.
                 * \return smoothen value.
                 */
                int convolve(const pandora::image8u &input_image,int x_center,int y_center)
                {
                    float sum = 0;
                    float sum_weight = 0;
                    
                    for (int y = -kernel_radius; y < kernel_radius; ++y)
                    {
                        for (int x = -kernel_radius; x < kernel_radius; ++x)
                        {
                            int x_neighbor = std::max(0,std::min(x_center+x,input_image.width()-1));
                            int y_neighbor = std::max(0,std::min(y_center+y,input_image.height()-1));
                            
                            float weight = std::exp(-(((x * x) + (y * y)) / (2.0 * sigma_squared)));
                            
                            sum += weight*input_image(x_neighbor,y_neighbor);
                            sum_weight += weight;
                        }
                    }
                    
                    return static_cast<pandora::image8u::value_type>(sum / sum_weight);
                }
                
                int kernel_radius;
                float sigma_squared;
            };
    }
}
}

#endif //__PANDORA_FILTER_GAUSSIAN_NAIVE_H__
