#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calcular o valor médio ponderado para escala de cinza
            int grey =
                round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Garante que grey está no intervalo 0-255
            grey = fmin(fmax(grey, 0), 255);

            // Atribuir o valor de cinza a todos os canais
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int sepiaRed =
                round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue);
            int sepiaGreen =
                round(.349 * pixel.rgbtRed + .686 * pixel.rgbtGreen + .168 * pixel.rgbtBlue);
            int sepiaBlue =
                round(.272 * pixel.rgbtRed + .534 * pixel.rgbtGreen + .131 * pixel.rgbtBlue);

            sepiaRed = fmin(fmax(sepiaRed, 0), 255);
            sepiaGreen = fmin(fmax(sepiaGreen, 0), 255);
            sepiaBlue = fmin(fmax(sepiaBlue, 0), 255);

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2;
             j++) // only needs to go through half of the pixels horizontaly and TRADE THEM
        {
            RGBTRIPLE pixel = image[i][j];

            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = pixel;
        }
    }
    return;
}

// Blur image
// Função para desfocar a imagem (blur)
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Criar uma cópia da imagem para não alterar os pixels enquanto calcula o blur
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j]; // Copiar o valor de cada pixel
        }
    }

    // Iterar por cada pixel da imagem
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;

            int count = 0; // Contar quantos pixels válidos para o cálculo

            // Para cada pixel, considera os vizinhos na área 3x3 gyokeres
            for (int a = i - 1; a <= i + 1; a++) // Loop vertical (linha)
            {
                for (int b = j - 1; b <= j + 1; b++) // Loop horizontal
                {
                    // Verifica se o pixel está dentro dos limites da imagem
                    if (a >= 0 && a < height && b >= 0 && b < width)
                    {
                        // Somar os valores dos componentes RGB para calcular a média
                        sumRed += copy[a][b].rgbtRed;
                        sumGreen += copy[a][b].rgbtGreen;
                        sumBlue += copy[a][b].rgbtBlue;
                        count++; // Contar o número de pixels válidos
                    }
                }
            }

            // Calcula a média de cada componente e aplica no pixel atual
            image[i][j].rgbtRed =
                round((float) sumRed / count); // Arredondar para o valor mais próximo
            image[i][j].rgbtGreen =
                round((float) sumGreen / count); // Arredondar para o valor mais próximo
            image[i][j].rgbtBlue =
                round((float) sumBlue / count); // Arredondar para o valor mais próximo
        }
    }

    return; // Não precisa retornar nada, pois estamos modificando a imagem diretamente
}
