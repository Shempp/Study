function [Path] = orderToPath(Order)

% Тест1 (Path=[1,2,4,3,8,5,9,6,7])
%Order=[1,1,2,1,4,1,3,1,1];
% Тест 2 (Path=[1,5,3,2,8,4,7,6])
%Order=[1,4,2,1,4,1,2,1];

SizeOfOrder=length(Order);
% Упорядоченный список L = (1 2 3 ... 52)
L=1:SizeOfOrder;
Path=zeros(1,SizeOfOrder);

for i=1:SizeOfOrder
    Path(i)=L(Order(i));
    L(Order(i))=[];
end

end

