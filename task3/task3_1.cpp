#include <iostream>
#include <vector>

int main()
{
	std::vector<int> v2(8, 0); //������ ������ � 8 ������

	std::cout << v2.capacity() << std::endl;// �������, ������� ��������� ����� ������� v2

	v2.push_back(0); //�������� �������� ��� ���� ���� � v2

	std::cout << v2.capacity() << std::endl; //�������, ������� ��������� ����� ������� v2 ������

	v2.reserve(10);							//����������� 10 � v2

	std::cout << v2.capacity() << std::endl;
	/*	
		������� ����������� �� 4, �.�. � 1,5 ���� (�� 8)
		��� ������� ��������������� ������, ��� ��� ���� � �������, ������ �� ����������
	*/

	std::vector<int> v1;			//������ ������ � ������ v1

	std::cout << v1.capacity()<<std::endl; //������� ����������  ���������, 
											//������� ������ ����� ��������� 
											//��� ��������� ��������������� ������������
	
	v1.reserve(10);							//����������� ������� 10 ��������� � ����� �������
	
	std::cout << v1.capacity() << std::endl; //����� ������� ���������� ��������� � �������

	
	for ( int i = 0; i < 11; ++i)	//�������� "��������� 11 ���������� � 10 ���������"
	{
		v1.push_back(0);		//�������� ������� � ����� ������� 
	}

	std::cout << v1.capacity() << std::endl;	//�������, ��� ��������� � ������ "�����������"

	/*
		������� ����������� �� 5, �.�. � 1,5 ���� (�� 10)
	*/

	std::vector<int> v3(200000000, 0);

	std::cout << v3.capacity() << std::endl;
	
	v3.push_back(0);							//��� ������� �������� � ��������� ������� ������ ��� ���� "����������" ����� ������: 
															// std::bad_alloc

	std::cout << v3.capacity() << std::endl;
}