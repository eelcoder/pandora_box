#ifndef __PANDORA_CONVOLUTION_H__
#define __PANDORA_CONVOLUTION_H__

#include <pandora/image.h>

namespace pandora
{
	typename<typename pixel_type,typename kernel_type<pixel_type> >
	class standard_convolution
	{
		  public:

		  	using image_type = image<pixel_type>;

		  	standard_convolution(int width,int height,int kernel_diameter,float sigma):
		  	 enlarged_image(width + kernel_diameter,height + kernel_diameter,0),
			 kernel(enlarged_image,kernel_diameter,sigma)
		  	{
		  	}

			void operator()(const image_type &input_image,image_type &output_image)
			{
				copy_with_padding(input_image,enlarged_image);

				auto output_value_iter = output_image.begin();
				for (auto y = neighbor.radius(); y < enlarged_image.height() - neighbor.radius(); ++y)
				{
					for (auto x = neighbor.radius(); x < enlarged_image.width() - neighbor.radius(); ++x)
					{
						int pixel_index = y * enlarged_image.width() + x;
						auto weight = kernel(pixel_index);
						*output_value_iter++ = weight;
					}
				}
			}
			
		  private:

		  	void copy_with_padding(const image_type &input_image)
		  	{
		  		//copy the input image into an intermediate buffer
				for(auto i=0;i<input_image.height();++i)	
				{	
					auto src_index = i*input_image.width();
					auto dst_index = i*enlarged_image.width() + neighbor.radius();
					std::copy_n(input_image.begin()+src_index,input_image.width(),enlarged_image.begin()+dst_index);
				}
		  	}

		  	image_type enlarged_image;
		  	kernel_type<pixel_type> kernel;
	};
}

#endif