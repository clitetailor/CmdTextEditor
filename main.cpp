#include <iostream>
/*/
 *
 *
 *
 *
 *
/*/

#include "Document.h"
#include "LinkList.h"

using namespace hedge;

int main()
{
	int line_size;
	std::cout << "line width:";
	std::cin >> line_size;
	
	Word word;
	Line line(line_size);
	LinkList<Line> document;
	
	std::cout << "Type your text here! (Enter Ctr+D to finish):" << std::endl;
	
	do
	{
		std::cin >> word;
		
		if (line.length() + word.length() > line_size)
		{
			if (word.length() > line_size)
			{
				Word frac;
				while (word.length() > line_size)
				{
					frac = word.split(line.length() + word.length() - line_size);
					line = line + frac;
					
					document.append(line);
					
					line.flush();
				}
				
				line = line + word;
			}
			else
			{
				document.append(line);
				
				line.flush();
				
				line = line + word;
			}
		}
		else
		{
			line = line + word;
		}
	} while (false == word.isEndOfFile());
	
	std::cout << std::endl;
	/*/
	 *
	 *
	 *
	 *
	 *
	/*/
	std::string align;
	std::cout << "align (left/center/right):";
	
	std::cin >> align;
	
	std::cout << std::endl;
	
	LinkList<Line>::Node * temp;
	
	if (align == "left")
	{
		for (temp = document.head(); temp->isNotTail(); temp = temp->next())
		{
			Line& current_line = temp->content();
			
			current_line.alignLeft();
		}
	}
	else if (align == "right")
	{
		for (temp = document.head(); temp->isNotTail(); temp = temp->next())
		{
			Line& current_line = temp->content();
			
			current_line.alignRight();
		}
	}
	else if (align == "center")
	{
		for (temp = document.head(); temp->isNotTail(); temp = temp->next())
		{
			Line& current_line = temp->content();
			
			current_line.alignCenter();
		}
	}
	
	for (temp = document.head(); temp->isNotTail(); temp = temp->next())
	{
		Line& current_line = temp->content();
		
		current_line.alignLeft();
		
		std::cout << current_line;
	}

	// Đọc vào độ dài của một dòng. Nếu độ dài của một dòng quá ngắn (bé hơn 18) thì thông báo và yêu cầu nhập lại.
	
	// Đọc vào từng từ một
	// Nếu độ dài của từ lớn hơn độ dài phần còn trống
	// 		Nếu độ dài từ lớn hơn độ dài dòng, cắt từ ra và chia vào hai dòng
	// 		Nếu độ dài từ bé hơn độ dài dòng, đặt dòng vừa tạo vào trong bộ nhớ, tạo dòng mới và thêm từ vào dòng tiếp theo
	// Nếu độ dài từ bé hơn độ dài phần còn trống đặt từ vào trong dòng.
	
	// Nếu trong từ chứa kí tự kết thúc, đặt kí tự null vào, kết thúc.
	// Nếu trong từ không chứa kí tự kết thúc đọc vào tiếp
	
	// Hỏi căn lề
	// In ra văn bản đã được căn lề
	
	return 0;
}