#include <stdio.h>

void main()
{
	float area, price, consumption, total_price;
	area = 325;
	price = 1.25;
	consumption = 0.22;
	total_price = (365 / 3) * consumption * price * area;
	printf("area of garden is %5.2f\n", area);
	printf("price for cubic feet is %5.2f\n", price);
	printf("water consumption for one cycle is %5.2f\n", consumption);
	printf("total price is %5.2f\n", total_price);
}
