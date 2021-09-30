#include <iostream>
#include <opencv2\opencv.hpp>
#include <cmath>

cv::Mat problem_a_rotate_forward(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	const double PI = 3.1415926;
	double sine = sin(angle * PI / 180);
	double cosine = cos(angle * PI / 180);

	int width = img.cols;
	int height = img.rows;

	if (angle <= 0) {
		int outputWidth = ceil(width * cosine + height * -1 * sine);
		int outputHeight = ceil(width * -1 * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int c = 0; c < img.channels(); c++) {
					output.at<cv::Vec3b>(int(cosine * i + sine * j + width * -1 * sine), int(-1 * sine * i + cosine * j))[c] = img.at<cv::Vec3b>(i, j)[c];
				}
			}

		}
	}
	else {
		int outputWidth = ceil(width * cosine + height * sine);
		int outputHeight = ceil(width * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				for (int c = 0; c < img.channels(); c++) {
					output.at<cv::Vec3b>(int(cosine * i + sine * j), int(-1 * sine * i + cosine * j + height * sine))[c] = img.at<cv::Vec3b>(i, j)[c];
				}
			}

		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("a_output", output); cv::waitKey(0);
	return output;
}

cv::Mat problem_b_rotate_backward(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	const double PI = 3.1415926;
	double sine = sin(angle * PI / 180);
	double cosine = cos(angle * PI / 180);

	int width = img.cols;
	int height = img.rows;

	if (angle <= 0) {
		int outputWidth = ceil(width * cosine + height * -1 * sine);
		int outputHeight = ceil(width * -1 * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < outputHeight; i++) {
			for (int j = 0; j < outputWidth; j++) {
				for (int c = 0; c < img.channels(); c++) {
					if (cosine * (i + width * sine) - sine * j >= 0 && cosine * (i + width * sine) - sine * j <= height)
						if (sine * (i + width * sine) + cosine * j >= 0 && sine * (i + width * sine) + cosine * j <= width)
							output.at<cv::Vec3b>(i, j)[c] = img.at<cv::Vec3b>(floor(cosine * (i + width * sine) - sine * j), floor(sine * (i + width * sine) + cosine * j))[c];
				}
			}

		}
	}
	else {
		int outputWidth = ceil(width * cosine + height * sine);
		int outputHeight = ceil(width * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < outputHeight; i++) {
			for (int j = 0; j < outputWidth; j++) {
				for (int c = 0; c < img.channels(); c++) {
					if (cosine * i + -1 * sine * (j - height * sine) >= 0 && cosine * i + -1 * sine * (j - height * sine) <= height)
						if (sine * i + cosine * (j - height * sine) >= 0 && sine * i + cosine * (j - height * sine) <= width)
							output.at<cv::Vec3b>(i, j)[c] = img.at<cv::Vec3b>(floor(cosine * i + -1 * sine * (j - height * sine)), floor(sine * i + cosine * (j - height * sine)))[c];
				}
			}

		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("b_output", output); cv::waitKey(0);
	return output;
}

cv::Mat problem_c_rotate_backward_interarea(cv::Mat img, double angle){
	cv::Mat output;

	//////////////////////////////////////////////////////////////////////////////
	//                         START OF YOUR CODE                               //
	//////////////////////////////////////////////////////////////////////////////

	const double PI = 3.1415926;
	double sine = sin(angle * PI / 180);
	double cosine = cos(angle * PI / 180);
	float area1, area2, area3, area4;
	float ratioA, ratioB, ratioC, ratioD;

	int width = img.cols;
	int height = img.rows;

	if (angle <= 0) {
		int outputWidth = ceil(width * cosine + height * -1 * sine);
		int outputHeight = ceil(width * -1 * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < outputHeight; i++) {
			for (int j = 0; j < outputWidth; j++) {
				for (int c = 0; c < img.channels(); c++) {
					if (cosine * (i + width * sine) - sine * j >= 0 && cosine * (i + width * sine) - sine * j + 1 <= height) {
						if (sine * (i + width * sine) + cosine * j >= 0 && sine * (i + width * sine) + cosine * j + 1 <= width) {
							ratioB = cosine * (i + width * sine) - sine * j - int(cosine * (i + width * sine) - sine * j);
							ratioC = sine * (i + width * sine) + cosine * j - int(sine * (i + width * sine) + cosine * j);
							ratioA = 1 - ratioB;
							ratioD = 1 - ratioC;

							area1 = img.at<cv::Vec3b>(floor(cosine * (i + width * sine) - sine * j + 1), floor(sine * (i + width * sine) + cosine * j))[c] * ratioB * ratioD;
							area2 = img.at<cv::Vec3b>(floor(cosine * (i + width * sine) - sine * j), floor(sine * (i + width * sine) + cosine * j))[c] * ratioA * ratioD;
							area3 = img.at<cv::Vec3b>(floor(cosine * (i + width * sine) - sine * j + 1), floor(sine * (i + width * sine) + cosine * j) + 1)[c] * ratioB * ratioC;
							area4 = img.at<cv::Vec3b>(floor(cosine * (i + width * sine) - sine * j), floor(sine * (i + width * sine) + cosine * j) + 1)[c] * ratioA * ratioC;

							output.at<cv::Vec3b>(i, j)[c] = int(area1 + area2 + area3 + area4);
						}
					}
				}
			}

		}
	}
	else {
		int outputWidth = ceil(width * cosine + height * sine);
		int outputHeight = ceil(width * sine + height * cosine);
		output = cv::Mat::zeros(cv::Size(outputWidth, outputHeight), CV_8UC3);

		for (int i = 0; i < outputHeight; i++) {
			for (int j = 0; j < outputWidth; j++) {
				for (int c = 0; c < img.channels(); c++) {
					if (cosine * i + -1 * sine * (j - height * sine) >= 0 && cosine * i + -1 * sine * (j - height * sine) + 1 <= height) {
						if (sine * i + cosine * (j - height * sine) >= 0 && sine * i + cosine * (j - height * sine) + 1 <= width) {
							ratioB = cosine * i + -1 * sine * (j - height * sine) - int(cosine * i + -1 * sine * (j - height * sine));
							ratioC = sine * i + cosine * (j - height * sine) - int(sine * i + cosine * (j - height * sine));
							ratioA = 1 - ratioB;
							ratioD = 1 - ratioC;

							area1 = img.at<cv::Vec3b>(floor(cosine * i + -1 * sine * (j - height * sine) + 1), floor(sine * i + cosine * (j - height * sine)))[c] * ratioB * ratioD;
							area2 = img.at<cv::Vec3b>(floor(cosine * i + -1 * sine * (j - height * sine)), floor(sine * i + cosine * (j - height * sine)))[c] * ratioA * ratioD;
							area3 = img.at<cv::Vec3b>(floor(cosine * i + -1 * sine * (j - height * sine) + 1), floor(sine * i + cosine * (j - height * sine)) + 1)[c] * ratioB * ratioC;
							area4 = img.at<cv::Vec3b>(floor(cosine * i + -1 * sine * (j - height * sine)), floor(sine * i + cosine * (j - height * sine)) + 1)[c] * ratioA * ratioC;

							output.at<cv::Vec3b>(i, j)[c] = int(area1 + area2 + area3 + area4);
						}
					}
				}
			}

		}
	}

	//////////////////////////////////////////////////////////////////////////////
	//                          END OF YOUR CODE                                //
	//////////////////////////////////////////////////////////////////////////////

	cv::imshow("c_output", output); cv::waitKey(0);
	return output;
}

cv::Mat Example_change_brightness(cv::Mat img, int num, int x, int y) {
	/*
	img : input image
	num : number for brightness (increase or decrease)
	x : x coordinate of image (for square part)
	y : y coordinate of image (for square part)

	*/
	cv::Mat output = img.clone();
	int size = 100;
	int height = (y + 100 > img.cols) ? img.cols : y + 100;
	int width = (x + 100 > img.rows) ? img.rows : x + 100;

	for (int i = x; i < width; i++)
	{
		for (int j = y; j < height; j++)
		{
			for (int c = 0; c < img.channels(); c++)
			{
				int t = img.at<cv::Vec3b>(i, j)[c] + num;
				output.at<cv::Vec3b>(i, j)[c] = t > 255 ? 255 : t < 0 ? 0 : t;
			}
		}

	}
	cv::imshow("output1", img);
	cv::imshow("output2", output);
	cv::waitKey(0);
	return output;
}

int main(void){

	double angle = -15.0f;

	cv::Mat input = cv::imread("lena.jpg");
	//Fill problem_a_rotate_forward and show output
	problem_a_rotate_forward(input, angle);
	//Fill problem_b_rotate_backward and show output
	problem_b_rotate_backward(input, angle);
	//Fill problem_c_rotate_backward_interarea and show output
	problem_c_rotate_backward_interarea(input, angle);
	//Example how to access pixel value, change params if you want
	Example_change_brightness(input, 100, 50, 125);
}