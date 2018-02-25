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
#ifndef __PANDORA_FILTER_GAUSSIAN_H__
#define __PANDORA_FILTER_GAUSSIAN_H__

#include <pandora/image.h>
#include <pandora/filters/details/gaussian_naive.h>
#include <pandora/filters/details/gaussian_separable.h>

namespace pandora
{
	namespace filter
	{
        /**
         * \brief generic interface of the gaussian filter.
         * \tparam gaussian filter implementation.
         */
        template<typename impl>
        class gaussian : impl
        {
         public:
            
           /**
            * \brief constructor.
            *
            * \param[in] kernel size.
            * \param[in] kernel sigma.
            */
            gaussian(int kernel_size,float sigma):
                impl(kernel_size,sigma)
            {
            }
            
            /**
             * \brief constructor.
             *
             * \param[in] image width.
             * \param[in] image height.
             * \param[in] kernel size.
             * \param[in] kernel sigma.
             */
            gaussian(int width,int height,int kernel_size,float sigma):
                impl(width,height,kernel_size,sigma)
            {
            }
            
            /**
             * \brief constructor.
             *
             * \param[in] input image.
             * \param[out] output image.
             */
            void operator()(const pandora::image8u &input_image, pandora::image8u &output_image)
            {
                impl::apply(input_image,output_image);
            }
        };
	}
    using gaussian_naive_filter = filter::gaussian<filter::details::gaussian_naive_impl>;
    using gaussian_separable_filter = filter::gaussian<filter::details::gaussian_separable_impl>;
}

#endif //__PANDORA_FILTER_GAUSSIAN_H__
