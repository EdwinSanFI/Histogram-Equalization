# Histogram Equalization

<p align="center">
<img src="Imagenes/Image-Eq.png">
</p>

This project showcases the implementation of the histogram equalization method using C and Python. The method is a popular technique for improving image contrast by redistributing pixel intensity values. This demo includes visualizations created with Matplotlib to display the differences in image contrast before and after applying the histogram equalization method.

## Introduction

Histogram equalization is an image processing technique used to enhance the contrast of an image by equalizing its intensity distribution. It does this by spreading out the most frequent intensity values, making the image histogram more uniform. This results in an image with improved contrast and enhanced details in both bright and dark regions.

Histogram equalization is a method in image processing of contrast adjustment using the image's histogram.

## Table of Contents
- [Overview](#)
- [Get Started](#)
- [How does it work?](#)
    - [Formula](#)
    - [Images](#)
- [Contributing](#)

## Getting started

To run the demo, follow these steps:

1. Clone the repository to your local machine:
```bash
git clone https://github.com/yourusername/histogram-equalization-demo.git
```

2. Change into the project directory:
```bash
cd histogram-equalization-demo
```

3. Install the required Python dependencies:
```bash
pip install -r requirements.txt
```

4. Compile the C implementation:
```bash
gcc -o equalization histogram_equalization.c
```

5. Run the Python script with the desired input image:
```
python histogram_equalization.py input_image.jpg
```

6. View the generated output images and histogram visualizations in the output folder.

## Image 1 grayscale
<div align="center">
    <div>
        <img src="/Imagenes/imaGray_1.jpg" height="250px">
        <img src="/Imagenes/imaGray_1_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaGray_1_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaGray_1_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Image 2 grayscale
<div align="center">
    <div>
        <img src="/Imagenes/imaGray_2.jpg" height="250px">
        <img src="/Imagenes/imaGray_2_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaGray_2_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaGray_2_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Image 3 grayscale
<div align="center">
    <div>
        <img src="/Imagenes/imaGray_3.jpg" height="250px">
        <img src="/Imagenes/imaGray_3_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaGray_3_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaGray_3_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Image 4 grayscale
<div align="center">
    <div>
        <img src="/Imagenes/imaGray_4.jpg" height="250px">
        <img src="/Imagenes/imaGray_4_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaGray_4_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaGray_4_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Image 1 RGBscale
<div align="center">
    <div>
        <img src="/Imagenes/imaRGB_1.jpg" height="250px">
        <img src="/Imagenes/imaRGB_1_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaRGB_1_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaRGB_1_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Image 2 RGBscale
<div align="center">
    <div>
        <img src="/Imagenes/imaRGB_2.jpg" height="250px">
        <img src="/Imagenes/imaRGB_2_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaRGB_2_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaRGB_2_histo_secuencial_img_nuevo.png" height="250px">
    </div>

</div>

## Image 3 RGBscale
<div align="center">
    <div>
        <img src="/Imagenes/imaRGB_3.jpg" height="250px">
        <img src="/Imagenes/imaRGB_3_eq_secuencial.jpg" height="250px">
    </div>
    <div>
        <img src="/Graficas/imaRGB_3_histo_secuencial_img_original.png" height="250px">
        <img src="/Graficas/imaRGB_3_histo_secuencial_img_nuevo.png" height="250px">
    </div>
</div>

## Learn More

To learn more about histogram equalization and image processing techniques, check out the following resources:

* [Wikipedia: Histogram Equalization](https://en.wikipedia.org/wiki/Histogram_equalization)

## Contributions & Feedback :speech_balloon:

I appreciate any feedback and suggestions to improve my projects, as well as contributions to the code. Feel free to create an issue or submit a pull request if you'd like to contribute.

## Connect With Me :handshake:
If you have any questions, want to discuss ideas or just want to connect, feel free to reach out to me on [LinkedIn](linkedin.com/in/edwin-san/), [GitHub](https://github.com/EdwinSanFI), [Twitter](https://twitter.com/home), [Instagram](instagram.com/edwinsanfi/).

<p align="center"> Thank you for visiting my Histogram Equalization repository, and I hope you enjoy learning! :smiley: </p>
