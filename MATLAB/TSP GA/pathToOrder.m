function [Order] = pathToOrder(Path)

% Тест1 (Order=[1,1,2,1,4,1,3,1,1])
%Path=[1,2,4,3,8,5,9,6,7];
% Тест 2 (Order=[1,4,2,1,4,1,2,1])
%Path=[1,5,3,2,8,4,7,6];

SizeOfPath=length(Path);
% Упорядоченный список L = (1 2 3 ... 52)
L=1:SizeOfPath;
Order=zeros(1,SizeOfPath);

for i=1:SizeOfPath
    IndexOfList=find(L==Path(i));
    Order(i)=IndexOfList;
    L(IndexOfList)=[];
end

end

