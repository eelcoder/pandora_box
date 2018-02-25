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
#include "catch.hpp"

#include <random>
#include <cmath>
#include "pandora/filters/gaussian.h"

SCENARIO("gaussian filter effectiveness", "[gaussian][filter]")
{
    GIVEN("A grayscale noisy image")
    {
        constexpr int image_width = 320;
        constexpr int image_height = 240;
        
        pandora::image8u input_image(image_width,image_height,1,1,0);
        pandora::image8u output_image(image_width,image_height,1,1,0);
        
        constexpr int kernel_diameter = 7;
        constexpr float sigma = 10.f;
        
        pandora::gaussian_naive_filter naive_filter(kernel_diameter,sigma);
        
        constexpr double mean = 128.0;
        constexpr double stddev = 5;
        std::default_random_engine generator;
        std::normal_distribution<double> dist(mean, stddev);
        
        // Add Gaussian noise
        for (auto& pixel_value : input_image)
        {
            pixel_value += dist(generator);
        }
        
        WHEN("apply the gaussian filter")
        {
            //apply the Gaussian smoothing
            naive_filter(input_image,output_image);
            
            THEN("the blurred image should have a low variance")
            {
                int mean = 0;
                //compute the mean
                for (auto pixel_value : output_image)
                {
                    mean += pixel_value;
                }
                mean/=output_image.size();
                
                //compute variance
                int variance = 0;
                for (auto pixel_value : output_image)
                {
                    variance += (pixel_value - mean)*(pixel_value - mean);
                }
                variance/=output_image.size();
                
                REQUIRE( std::sqrt(variance) == 0 );
            }
        }
    }
}

SCENARIO("gaussian filter implementations similarity", "[gaussian][filter]")
{
	GIVEN("A grayscale noisy image")
	{
        constexpr int image_width = 320;
        constexpr int image_height = 240;
        
        pandora::image8u input_image(image_width,image_height,1,1,0);
        pandora::image8u output_image1(image_width,image_height,1,1,0);
        pandora::image8u output_image2(image_width,image_height,1,1,0);
        
        constexpr int kernel_diameter = 5;
        constexpr float sigma = 10.f;
        
        pandora::gaussian_naive_filter naive_filter(kernel_diameter,sigma);
        pandora::gaussian_separable_filter separable_filter(image_width,image_height,kernel_diameter,sigma);
        
        // Define random generator with Gaussian distribution
        constexpr double mean = 128.0;
        constexpr double stddev = 50;
        std::default_random_engine generator;
        std::normal_distribution<double> dist(mean, stddev);
        
        // Add Gaussian noise
        for (auto& pixel_value : input_image)
        {
            pixel_value += dist(generator);
        }
        
		WHEN("apply the gaussian blur using two different methods")
		{
            //apply the Gaussian smoothing
            naive_filter(input_image,output_image1);
            separable_filter(input_image,output_image2);
            
			THEN("the blurred images should be similar")
			{
                bool are_equal = std::equal(output_image1.begin(), output_image1.end(), output_image2.begin(),
                [](auto a, auto b)
                {
                    return std::abs(a-b) <=1;
                });
                REQUIRE(are_equal == true );
			}
		}
	}
}
