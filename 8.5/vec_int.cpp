#include <iostream>
#include <vector>

int main() {
	std::vector<int> vi = { 1, 2, 3, 4, 5 };
	auto iter = vi.begin();

	while (iter != vi.end())
	{
		if (*iter % 2) {
			iter = vi.insert(iter, *iter);
			iter += 2;
		}
		else
			++iter; // dead loop!
	}

	for (iter = vi.begin(); iter != vi.end(); ++iter)
		std::cout << *iter << '\t';
	std::cout << std::endl;
	return 0;
}