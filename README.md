# Social_Network-in-Data-Structures

We will be implementing a social network system, which consists of various users connected in a network of a non-linear structure. In this course, we have learnt that non-linear data structures are connected through pointers and are stored in non-contiguous locations. In the case of a network, a non-linear data structure is helpful, which helps you jump to various nodes without the need of knowing a certain fixed size of the data structure. Some of the important non-linear data structures you’ve learnt are trees and graphs.

# Logical units and terminologies of the system

1.<b> User</b>: Essentially, a user is represented by a node in the data structure. This node contained information about the user, such as ID, name, number of friends, and a list of friends.
<br>
2.<b> Connections</b>: Users in a system are connected to one another based on the ID. The users do not have bidirectional connections. No connection forms a loop. Users are segregated in the system based on IDs, all users have first connections where they connect with users of ID less than their own and have second connections where they connect with users of ID greater than their own. This means that each user has at max two connections - first and second - or only one of those or none at all.
<br>
3. <b>Friends</b>: Each user has a list of friends or no friends at all. This list is a part of user information. Connections of the users may not necessarily be their friends. This means that a user has at most two connections but can have any number of friends. While the user can name any number of friends, only those friends who are a part of the network can be added and stored in the list. Here’s a small diagram to help you understand the constraints of the system.
<br>
![friends](https://user-images.githubusercontent.com/103581128/201150138-d5a2ef33-a815-4eed-92b9-9958b3b3dbd5.png)
<br>
In the above diagram, you can understand the structure of the system based on the USER [ID] named in each node. Friends is a list that is initially given as input, the friend IDs marked as red are not present in the tree, hence the final list of friends stored (next line) contains only the friends that exist in the tree.


# Learning Outcomes

1. Cope with abstractions depicting real-world entities.
2. Choosing appropriate data-structures for the right design.
3. Writing reusable and modular code.
4. Strengthen memory management in C and avoid dangling pointers and memory leaks while using dynamic data-structures like linked lists.
5. Getting familiar with the various operations of a BST.
6. Rearranging the nodes in BST.
