/*
 * main.c
 *
 *  Created on: Sep 1, 2021
 *      Author: tocru
 */


#include "main.h"



int main(void)
{
  hwInit();
  apInit();

  apMain();

  return 0;
}
