# Semester-Project :

Making an Inventory management system. The main job of this project is maintain the records of inventory items of FCIT.
The project is divided into 8 modules:

1- To add items in the Inventory: i have made a structure that contains all the instances of an item. So as the user want to add an item, this program stores that record in a structure and then add its to data file.

2- To view items: The view function reads all the records from the data file and displays them in a tabular mannner.

3- To search: The search functions allows you search a particular record based on the item no. or item ID.

4- Update Function: The update functions allows you not only to view a particular item but also to make changes in its records.

5- Delete Function: The delete function will alow us to delete a particular record in the data. I was not aware of any function to delete the data, so rather i am creating a temporary file and write all my data into  it, except the one to be deleted. Then i remove the original data file and rename my temporary file to the original data file.

6- Assign Functions: This program requires us to keep the names of all the faculty members who have borrowed a specific item. The assign function reads the name of the person and then stores that name in the Allocated_to array (array to names of the members). As soon as an item in borrowed its item count reduces by one and the members count increases by one.

7: Retrieve Function: Opposite of assign function, this function allows you to retrieve an item from a member, Consquently his/her name is removed from the Allocate_to array, item count increases by one and people count decreases by one.

8- View members: This functions provides a list of all members who have borrowed a particular item.

This whole project is done using Binary File Handling. ALl the data has been stored and retrieved from files.
