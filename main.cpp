#include <QCoreApplication>
#include <QDebug>
#include <QLibraryInfo>

#ifdef _WIN32
#  include <qt_windows.h>
#endif

#include <iostream>

#include <orm/db.hpp>
#include <orm/libraryinfo.hpp>
#include <orm/tiny/model.hpp>

using Orm::Constants::ID;
using Orm::Constants::NAME;
using Orm::Constants::NEWLINE;
using Orm::Constants::QSQLITE;
using Orm::Constants::QUOTE;
using Orm::Constants::SPACE;
using Orm::Constants::check_database_exists;
using Orm::Constants::database_;
using Orm::Constants::driver_;

using Orm::DB;
using Orm::LibraryInfo;
using Orm::Tiny::Model;
using Orm::Utils::Helpers;

class Post final : public Model<Post>
{
    friend Model;
    using Model::Model;
};

std::ostream &operator<<(std::ostream &os, const QString &value)
{
    return os << value.toUtf8().constData();
}

void run()
{
    // Create the SQLite database connection
    // Ownership of a unique_ptr()
    auto manager = DB::create({
        {driver_,   QSQLITE},
        {database_, qEnvironmentVariable("TINYORM_HELLOWORLD_DB_SQLITE_DATABASE",
                                         "../../HelloWorld.sqlite3")},
        {check_database_exists, true},
    });

    // Print Qt and TinyORM builds information
    std::cout << QLibraryInfo::build() << NEWLINE
              << LibraryInfo::build() << NEWLINE << NEWLINE;

    // Select using QueryBuilder
    {
        auto posts = DB::select("select * from posts");

        while(posts.next())
            std::cout << posts.value(ID).toULongLong() << SPACE << QUOTE
                      << posts.value(NAME).toString() << QUOTE << NEWLINE;
    }
    // Select using ORM (Post model)
    {
        const auto posts = Post::all();

        for (const auto &post : posts)
            std::cout << post.getAttribute<quint64>(ID) << SPACE << QUOTE
                      << post.getAttribute<QString>(NAME) << QUOTE << NEWLINE;
    }
}

int main(int argc, char *argv[])
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
//    SetConsoleOutputCP(1250);
#endif

    try {
        /* Needed from Qt v6.5.3 to avoid:
           qt.core.qobject.connect: QObject::connect(QObject, Unknown): invalid nullptr parameter */
        const QCoreApplication app(argc, argv);

        run();
    } catch (const std::exception &e) {

        Helpers::logException(e);

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
   Expected output:

   TinyORM 0.34.0 (x86_64-little_endian-llp64 shared debug build; by MSVC 2022 (1936))
   Executed prepared query (8ms, -1 results, 0 affected, tinyorm_default) : select * from posts
   1 "First Post"
   2 "Second Post"
   Executed prepared query (0ms, -1 results, 0 affected, tinyorm_default) : select * from "posts"
   1 "First Post"
   2 "Second Post"
*/
