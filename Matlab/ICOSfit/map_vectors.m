function [C,IA,IB] = map_vectors(A, B)
% [IA,IB] = map_vectors(A, B);
% Vectors A and B must be monotonic. The unique values in A and B create
% a third vector, C, satisfying the relationship:
%   C(IA) == A
%   C(IB) == B
% If all(IA), then all(C==A)
% 
% See also union
if ~isvector(A) || ~isvector(B)
  error('map_vectors: Inputs must be vectors');
end
if ~all(diff(sort(A))>0) || ~all(diff(sort(B))>0)
  error('map_vectors: Inputs must be strictly monotonic');
end
if isrow(A); A = A'; end
if isrow(B); B = B'; end
C = unique([A; B]);
IC = 1:length(C);
IA = interp1(C,IC,A);
IB = interp1(C,IC,B);
