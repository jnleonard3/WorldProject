/**
 * \file NodeConnectivityData.h
 * \author Jon Leonard
 * \date 2014/02/10
 * \copyright The BSD 2-Clause License
 */
#ifndef NODE_CONNECTIVITY_DATA_H_
#define NODE_CONNECTIVITY_DATA_H_

/**
 * \class NodeConnectivityData
 */
class NodeConnectivityData : public NodeData {
public:
	NodeConnectivityData(unsigned long revisionId):NodeData(revisionId){}
private:
};

#endif