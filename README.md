👔 Smart Digital Closet & Outfit Recommendation System

📖 About the Project

Smart Digital Closet is a C++ console application developed as an Object-Oriented Programming (OOP) project. The system provides users with a digital wardrobe where they can organize their clothing items and receive outfit suggestions according to different preferences and conditions.

The project focuses on applying fundamental OOP concepts to a practical, user-oriented system while maintaining user-specific wardrobe data through file handling.

🎯 Project Objectives

• Create a digital representation of a user’s wardrobe
• Provide an organized way to manage clothing items
• Generate suitable outfit combinations
• Apply fundamental Object-Oriented Programming concepts
• Maintain user data across different sessions
• Demonstrate practical implementation of C++ file handling

⚙️ Core Features

• User registration and login
• Personal wardrobe management
• Adding clothing items
• Viewing wardrobe items
• Editing existing clothing information
• Deleting clothing items
• Outfit recommendation system
• Multi-user support
• Persistent file-based data storage

👗 Wardrobe Categories

• Upper Wear
• Lower Wear
• Shoes

✨ Outfit Recommendation

The recommendation system considers several factors when generating outfit combinations:

• Occasion
• Season
• Color compatibility
• Shoe compatibility
• Available clothing combinations

Based on these factors, the system suggests suitable outfits from the user’s available wardrobe.

🧩 Object-Oriented Programming Concepts

Encapsulation
Clothing-related attributes are controlled within their respective classes and accessed through appropriate member functions.

Inheritance
The Upper, Lower, and Shoes classes inherit common properties and functionality from the ClothingItem base class.

Polymorphism
The displayItem() function is implemented as a virtual function in the base class and overridden by derived classes.

Abstraction
Complex operations such as file handling, wardrobe management, editing, deletion, and recommendation processing are handled internally through simplified functions.

💻 Technologies Used

• C++
• Object-Oriented Programming
• File Handling
• Console Application

💾 Data Storage

The application uses text files to preserve information between program sessions:

• users.txt — stores user registration and authentication information
• clothes.txt — stores clothing and wardrobe records

The system maintains separate wardrobe information for different users.

🧪 Testing

The application was tested through different functional scenarios:

• User registration
• Login authentication
• Duplicate username validation
• Adding clothing items
• Viewing wardrobe
• Editing clothing details
• Deleting clothing items
• Outfit recommendations
• Multi-user functionality
• Data persistence

🚀 Future Enhancements

• Introduce STL containers such as vector
• Add advanced search and filtering
• Add outfit history and saved combinations
• Improve color-matching functionality
• Add weather-based outfit recommendations
• Develop a graphical user interface
• Enhance the recommendation engine

👨‍💻 Project Team

Team Leader
Urneeb Zahra — 251301002

Team Members
Muhammad Saad Asghar — 251301049
M. Ahmed Bin Kashif Malik — 251301047

🎓 Institution

Institute of Space Technology (IST), Islamabad
Department of Computer Sciences

📄 Project Documentation

The complete project report and relevant documentation are available in the docs folder.
