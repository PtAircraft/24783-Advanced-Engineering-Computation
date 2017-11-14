#include "astar.h"


std::vector <YsShellExt::VertexHandle> A_Star(const YsShellExt &shl,YsShellExt::VertexHandle startVtHd,YsShellExt::VertexHandle goalVtHd)
{
	return std::vector <YsShellExt::VertexHandle>(); // Path not found.
}

std::vector <YsShellExt::VertexHandle> A_Star_ReconstructPath(
    const YsShellExt &shl,const std::unordered_map <YSHASHKEY,YsShellExt::VertexHandle> &cameFrom,YsShellExt::VertexHandle current)
{
	std::vector <YsShellExt::VertexHandle> path;
	return path;
}
