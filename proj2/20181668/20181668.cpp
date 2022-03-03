#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "yj0616!";
const char* db = "prj2";

MYSQL* connection = NULL;
MYSQL conn;
MYSQL_RES* sql_result;
MYSQL_ROW sql_row;

// function for type 1
void type1() {
	int k = 0, t = 0, state = 0, inp = 0;
	char b[20];
	printf("-------- TYPE 1 --------\n\n");
	printf("** Show the sales trends for a particular brand over the past k years. **\n");
	while (1) {
		// input brand name
		printf("Which brand? : ");
		scanf("%s", b);
		// input k
		printf("Which K? (0 : exit this query) : ");
		scanf("%d", &k);
		// if k is 0, then close type 1
		if (k == 0) break;
		char q1[500];
		sprintf(q1, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), YEAR(v.purchase_date) AS pyr FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name WHERE v.on_sale = \"N\" and b.brand_name = \"%s\" and (2021 - YEAR(v.purchase_date) > 0) and (2021 - YEAR(v.purchase_date) <= %d) GROUP BY pyr", b, k);
		state = 0;
		state = mysql_query(connection, q1);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			// sale trends for a particular brand
			printf("===============================================================\n");
			printf(" brand_name          unit             dollar            year\n");
			printf("===============================================================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%12s           %s           %9s            %4s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

		printf("\n----------- TYPE 1-1 -----------\n\n");
		printf("** Break this data out by gender of the buyer **\n");
		printf("** 0 : skip **\n** 1 : show results **\nInput : ");
		scanf("%d", &inp);
		if (inp == 1) {
			char q11[500];
			sprintf(q11, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), YEAR(v.purchase_date) AS pyr, pc.gender FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name JOIN person_customers AS pc ON v.customer_name = pc.customer_name AND v.phone_number = pc.phone_number WHERE v.on_sale = \"N\" and b.brand_name = \"%s\" and (2021 - YEAR(v.purchase_date) > 0) and (2021 - YEAR(v.purchase_date) <= %d) GROUP BY pyr, pc.gender", b, k);
			state = 0;
			state = mysql_query(connection, q11);
			if (state == 0) {
				sql_result = mysql_store_result(connection);
				// sale trends for a particular brand for each gender
				printf("=============================================================================\n");
				printf(" brand_name          unit             dollar           year           gender\n");
				printf("=============================================================================\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%12s           %s           %9s           %4s            %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
				}
				printf("\n");
				mysql_free_result(sql_result);
			}
		}
		printf("\n---------- TYPE 1-1-1 ----------\n\n");
		printf("** Break this data out by gender of the buyer and then break out by income **\n");
		printf("** 0 : skip **\n** 1 : show results **\nInput : ");
		scanf("%d", &inp);
		if (inp == 1) {
			char q111[700];
			sprintf(q111, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), YEAR(v.purchase_date) AS pyr, pc.gender, c.annual_income FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name JOIN person_customers AS pc ON v.customer_name = pc.customer_name AND v.phone_number = pc.phone_number JOIN customers AS c ON v.customer_name = c.customer_name AND v.phone_number = c.phone_number WHERE v.on_sale = \"N\" and b.brand_name = \"%s\" and (2021 - YEAR(v.purchase_date) > 0) and (2021 - YEAR(v.purchase_date) <= %d) GROUP BY pyr, pc.gender, c.annual_income ORDER BY pyr, c.annual_income DESC", b, k);
			state = 0;
			state = mysql_query(connection, q111);
			if (state == 0) {
				sql_result = mysql_store_result(connection);
				// sale trends for a particular brand for each gender and income
				printf("==============================================================================================\n");
				printf(" brand_name          unit             dollar           year         gender         income\n");
				printf("==============================================================================================\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%12s           %s           %9s           %4s           %s           %9s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);
				}
				printf("\n");
				mysql_free_result(sql_result);
			}
		}
	}
	return;
}

// function for type 2
void type2() {
	int k = 0, t = 0, state = 0, inp = 0;
	printf("-------- TYPE 2 --------\n\n");
	printf("** Show sales trends for various brands over the past k months. **\n");
	while (1) {
		// input k
		printf("Which K? (0 : exit this query) : ");
		scanf("%d", &k);
		// if k is 0, then close type 2
		if (k == 0) break;
		char q2[500];
		sprintf(q2, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), MONTH(v.purchase_date) AS pm FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name WHERE (YEAR(v.purchase_date) = 2021) AND v.on_sale = \"N\" and (6 - MONTH(v.purchase_date) > 0) and (6 - MONTH(v.purchase_date) <= %d) GROUP BY b.brand_name, pm ORDER BY pm", k);
		state = 0;
		state = mysql_query(connection, q2);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			// sale trends for brands
			printf("===========================================================\n");
			printf(" brand_name          unit             dollar          month\n");
			printf("===========================================================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%12s           %2s           %9s          %2s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

		printf("\n----------- TYPE 2-1 -----------\n\n");
		printf("** Break this data out by gender of the buyer **\n");
		printf("** 0 : skip **\n** 1 : show results **\nInput : ");
		scanf("%d", &inp);
		if (inp == 1) {
			char q21[700];
			sprintf(q21, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), MONTH(v.purchase_date) AS pm, pc.gender FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name JOIN person_customers AS pc ON v.customer_name = pc.customer_name AND v.phone_number = pc.phone_number WHERE YEAR(v.purchase_date) = 2021 AND v.on_sale = \"N\" and (6 - MONTH(v.purchase_date) > 0) and (6 - MONTH(v.purchase_date) <= %d) GROUP BY b.brand_name, pm, pc.gender ORDER BY pm", k);
			state = 0;
			state = mysql_query(connection, q21);
			if (state == 0) {
				sql_result = mysql_store_result(connection);
				// sale trends for a particular brand for each gender
				printf("=====================================================================================\n");
				printf(" brand_name          unit              dollar         month        gender\n");
				printf("=====================================================================================\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%12s           %2s           %9s           %2s          %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
				}
				printf("\n");
				mysql_free_result(sql_result);
			}
		}

		printf("\n---------- TYPE 2-1-1 ----------\n\n");
		printf("** Break this data out by gender of the buyer and then break out by income **\n");
		printf("** 0 : skip **\n** 1 : show results **\nInput : ");
		scanf("%d", &inp);
		if (inp == 1) {
			char q211[700];
			sprintf(q211, "SELECT b.brand_name, COUNT(v.VIN), SUM(v.sale_price), MONTH(v.purchase_date) AS pm, pc.gender, c.annual_income FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name JOIN customers AS c ON v.customer_name = c.customer_name AND v.phone_number = c.phone_number JOIN person_customers AS pc ON v.customer_name = pc.customer_name AND v.phone_number = pc.phone_number WHERE YEAR(v.purchase_date) = 2021 AND v.on_sale = \"N\" and (6 - MONTH(v.purchase_date) > 0) and (6 - MONTH(v.purchase_date) <= %d) GROUP BY b.brand_name, pm, pc.gender, c.annual_income ORDER BY pm, c.annual_income DESC", k);
			state = 0;
			state = mysql_query(connection, q211);
			if (state == 0) {
				sql_result = mysql_store_result(connection);
				// sale trends for a particular brand for each gender and income
				printf("=====================================================================================================\n");
				printf(" brand_name          unit             dollar         month         gender         income\n");
				printf("=====================================================================================================\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%12s           %2s           %9s           %2s           %s          %9s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);
				}
				printf("\n");
				mysql_free_result(sql_result);
			}
		}
	}
	return;
}

// function for type 3
void type3() {
	int k = 0, t = 0, state = 0;
	char fd[12];
	char sd[12];
	char sup_name[10];
	printf("-------- TYPE 3 --------\n\n");
	printf("** Find that transmissions made by supplier (company name) between two given dates are defective. **\n");
	while (1) {
		printf("** 0 : exit this query **\n** 1 : continue this query **\nInput : ");
		scanf("%d", &k);
		if (k == 0) break;
		// input supplier name
		printf("Supplier name? : ");
		scanf("%s", sup_name);
		// input dates
		printf("Which start date? (yyyy-mm-dd): ");
		scanf("%s", fd);
		printf("Which finish date? (yyyy-mm-dd): ");
		scanf("%s", sd);

		char q3[500];
		sprintf(q3, "SELECT * FROM supply_parts WHERE supplier_name = \"%s\" AND part_type = \"transmission\" AND supply_date between DATE('%s') AND DATE('%s')", sup_name, fd, sd);
		state = 0;
		state = mysql_query(connection, q3);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			// all information
			printf("All information\n");
			printf("=================================================================================\n");
			printf(" supplier_name          part_type             VIN                  supply_date\n");
			printf("=================================================================================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%s                  %s           %12s         %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

		char q33[500];
		sprintf(q33, "SELECT * FROM supply_for_sale WHERE supplier_name = \"%s\" AND part_type = \"transmission\" AND manufacture_date <= DATE('%s')", sup_name, fd);
		state = 0;
		state = mysql_query(connection, q33);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			// for reference record
			printf("Record of suppliment from plants to suppliers\n");
			printf("======================================================================================\n");
			printf(" plant_name        supplier_name         part_type         manufacture_date\n");
			printf("======================================================================================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%s                 %s           %s          %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

		while (1) {
			printf("------- Subtypes in TYPE 3 -------\n\n");
			printf("\t1. TYPE 3-1.\n");
			printf("\t2. TYPE 3-2.\n");
			printf("----------------------------------\n\n");
			// input sub type
			printf("Which subtype? (0 : exit this query) : ");
			scanf("%d", &t);
			if (t == 0)break;
			// sub type 1
			else if (t == 1) {
				printf("\n----------- TYPE 3-1 -----------\n\n");
				char q31[500];
				sprintf(q31, "SELECT sp.VIN, v.customer_name, v.phone_number, sp.supply_date, v.purchase_date FROM supply_parts AS sp JOIN vehicles AS v ON v.VIN = sp.VIN WHERE sp.supplier_name = \"%s\" AND part_type = \"transmission\" AND v.on_sale = \"N\" AND sp.supply_date between DATE('%s') AND DATE('%s')", sup_name, fd, sd);
				state = 0;
				state = mysql_query(connection, q31);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("===============================================================================================\n");
					printf(" VIN                customer_name       customer_phone       supply_date        sale_date\n");
					printf("===============================================================================================\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%12s             %9s       %9s           %s        %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
					}
					printf("\n");
					mysql_free_result(sql_result);
				}
			}
			// sub type 2
			else if (t == 2) {
				printf("\n----------- TYPE 3-2 -----------\n\n");
				char q32[700];
				sprintf(q32, "SELECT v.dealer_name, v.d_address, sp.VIN, o.transmission, sp.supply_date, v.purchase_date FROM vehicles AS v JOIN supply_parts AS sp ON v.VIN = sp.VIN JOIN options AS o ON o.model_name = v.model_name AND o.color = v.color AND o.engine = v.engine AND o.transmission = v.transmission WHERE sp.supplier_name = \"%s\" AND part_type = \"transmission\" AND v.on_sale = \"N\" AND sp.supply_date between DATE('%s') AND DATE('%s')", sup_name, fd, sd);
				state = 0;
				state = mysql_query(connection, q32);
				if (state == 0) {
					sql_result = mysql_store_result(connection);
					printf("==============================================================================================================\n");
					printf(" dealer                         VIN                transmission        supply_date              sale_date\n");
					printf("==============================================================================================================\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s %s           %12s            %s            %s               %s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5]);
					}
					printf("\n");
					mysql_free_result(sql_result);
				}
			}
			else printf("Invalid subtype\n");
		}
	}
	return;
}

// function for type 4
void type4() {
	int k = 0, y = 0;
	printf("-------- TYPE 4 --------\n\n");
	printf("** Find the top k brands by dollar-amount sold by the year **\n");
	while (1) {
		// input k
		printf("Which K? (0 : exit this query) : ");
		scanf("%d", &k);
		if (k == 0) break;
		// input year
		printf("Which year? : ");
		scanf("%d", &y);
		char q4[500];
		sprintf(q4, "SELECT b.brand_name, SUM(v.sale_price) FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name WHERE v.on_sale = \"N\" AND YEAR(v.purchase_date) = %d GROUP BY b.brand_name ORDER BY SUM(v.sale_price) DESC LIMIT %d", y, k);
		int state = 0;
		state = mysql_query(connection, q4);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("=============================\n");
			printf(" brand_name          dollar\n");
			printf("=============================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%12s           %s\n", sql_row[0], sql_row[1]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

	}
	return;
}

// function for type 5
void type5() {
	int k = 0, y = 0;
	printf("-------- TYPE 5 --------\n\n");
	printf("** Find the top k brands by until sales by the year **\n");
	while (1) {
		// input k
		printf("Which K? (0 : exit this query) : ");
		scanf("%d", &k);
		if (k == 0) break;
		// input year
		printf("Which year? : ");
		scanf("%d", &y);
		char q5[500];
		sprintf(q5, "SELECT b.brand_name, COUNT(v.VIN) AS unit FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name JOIN brands AS b ON m.brand_name = b.brand_name WHERE v.on_sale = \"N\" AND YEAR(v.purchase_date) = %d GROUP BY b.brand_name ORDER BY COUNT(v.VIN) DESC LIMIT %d", y, k);
		int state = 0;
		state = mysql_query(connection, q5);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("=========================\n");
			printf(" brand_name          unit\n");
			printf("=========================\n");
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				printf("%12s           %s\n", sql_row[0], sql_row[1]);
			}
			printf("\n");
			mysql_free_result(sql_result);
		}

	}
	return;
}

// function for type 6
void type6() {
	int flag = 0, m = 0, cnt = 0;
	printf("-------- TYPE 6 --------\n\n");
	printf("** In what month(s) do convertibles sell best? **\n");
	while (1) {
		// input exit or continue
		printf("** 0 : exit this query **\n** 1 : continue this query **\nInput : ");
		scanf("%d", &flag);
		printf("\n");
		if (flag == 0) break;
		char q6[500];
		sprintf(q6, "SELECT MONTH(v.purchase_date) as pc_month, COUNT(VIN) FROM vehicles AS v JOIN models AS m ON v.model_name = m.model_name WHERE m.body_style = \"Convertible\" AND v.on_sale = \"N\" GROUP BY pc_month ORDER BY COUNT(VIN) DESC");
		int state = 0;
		state = mysql_query(connection, q6);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("Best month is ");
			cnt = 0;
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				if (cnt == 0) {
					printf("%s (unit : %s) ", sql_row[0], sql_row[1]);
					m = atoi(sql_row[1]);
				}
				else if (atoi(sql_row[1]) == m)
					printf(", %s (unit : %s) ", sql_row[0], sql_row[1]);
				cnt++;
			}
			printf("\n\n");
			mysql_free_result(sql_result);
		}
	}
	return;
}

// function for type 7
void type7() {
	int flag = 0, m = 0, cnt = 0;
	printf("-------- TYPE 7 --------\n\n");
	printf("** Find those dealers who keep a vehicle in inventory for the longest average time. **\n");
	while (1) {
		// input exit or continue
		printf("** 0 : exit this query **\n** 1 : continue this query **\nInput : ");
		scanf("%d", &flag);
		printf("\n");
		if (flag == 0) break;
		char q7[500];
		sprintf(q7, "SELECT dealer_name, d_address, AVG(timestampdiff(DAY, production_date, CURDATE())) as avg_date FROM vehicles WHERE on_sale = \"Y\" GROUP BY dealer_name, d_address ORDER BY avg_date DESC");
		int state = 0;
		state = mysql_query(connection, q7);
		if (state == 0) {
			sql_result = mysql_store_result(connection);
			printf("Dealer is ");
			cnt = 0;
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				if (cnt == 0) {
					printf("%s %s (day : %s) ", sql_row[0], sql_row[1], sql_row[2]);
					m = atoi(sql_row[2]);
				}
				else if (atoi(sql_row[2]) == m)
					printf(", %s %s (day : %s) ", sql_row[0], sql_row[1], sql_row[2]);
				cnt++;
			}
			printf("\n\n");
			mysql_free_result(sql_result);
		}
	}
	return;
}

int main(void) {
	// initialize
	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");
	// make connection using information of user db
	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	// connection fail
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	// connection success
	else
	{
		printf("Connection Succeed\n");
		// select database
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		// open CRUID file
		FILE* fp = fopen("20181668.txt", "r");
		char temp[500];
		// read a line and execute query until EOF
		while (1) {
			if (feof(fp)) break;
			fgets(temp, 500, fp);
			mysql_query(connection, temp);
		}
		if (temp != NULL)
			mysql_query(connection, temp);
		fclose(fp);

		int typeno;

		// start the program until user select quit menu
		while (1) {
			printf("-------- SELECT QUERY TYPES --------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n");
			scanf("%d", &typeno);
			if (typeno == 0) break;
			else if (typeno == 1) type1();
			else if (typeno == 2) type2();
			else if (typeno == 3) type3();
			else if (typeno == 4) type4();
			else if (typeno == 5) type5();
			else if (typeno == 6) type6();
			else if (typeno == 7) type7();
			else printf("Invalid type number\n");
		}

		fp = fopen("20181668_2.txt", "r");
		// read a line and execute query until EOF
		while (1) {
			if (feof(fp)) break;
			fgets(temp, 500, fp);
			mysql_query(connection, temp);
		}
		fclose(fp);

		mysql_close(connection);
	}

	return 0;
}
