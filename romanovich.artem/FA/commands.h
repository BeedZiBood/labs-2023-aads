#ifndef COMMANDS_H
#define COMMANDS_H
#include <functional>
#include <iosfwd>
#include <memory>
#include "../common/redblack_tree.h"
#include "hashtable.h"
namespace romanovich
{
  class CommandHandler
  {
  public:
    explicit CommandHandler(std::istream &, std::ostream &);
    ~CommandHandler();
    CommandHandler &operator=(CommandHandler &&) = delete;
    void operator()(const std::string &command);
  private:
    std::istream &in_;
    std::ostream &out_;
    RedBlackTree< std::string, std::function< void() > > processor_;
    std::vector< std::pair< std::string, romanovich::HashTable > > *dictionaries_;
    void addWordToDict();//
    void addDict();//
    void addTranslation();//
    void removeWord();//
    void removeTranslation();//
    void searchTranslations();
    void searchWords();
    void countWords();
    void countTranslations();
    void exportToFile();
    void help();
    void addMissingWords();
    void createLevelDict();
    void mergeDicts();
    void printDicts(std::ostream &out);
  };
}
#endif
