function [DistanceMatrix] = coordsToMatrix(X,Y)
LengthOfCoordsX=length(X);
LengthOfCoordsY=length(Y);
if LengthOfCoordsX~=LengthOfCoordsY
    error('Error in coordsToMatrix. Length of X not equal to Y');
end
for i=1:LengthOfCoordsX
    for j=1:LengthOfCoordsX
        DistanceMatrix(i,j)=sqrt((X(i)-X(j))^2+(Y(i)-Y(j))^2);
    end
end
end

