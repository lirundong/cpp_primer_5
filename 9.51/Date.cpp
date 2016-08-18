#include "Date.h"

int main(int argc, char *argv[]) {
	std::string date_temp;
	Date testDate1;
	while (std::cin >> date_temp) {
		if (date_temp == "Q")
			break;
		else {
			testDate1.reload(date_temp);
			testDate1.display_date();
		}
	}

	return 0;
}