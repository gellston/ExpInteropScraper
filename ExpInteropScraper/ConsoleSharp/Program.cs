namespace ConsoleSharp
{
    internal class Program
    {
        static void Main(string[] args)
        {


            var scrapper = new SharpScrapperLib.SimpleScraper();
            var html = scrapper.GetHtml("https://www.naver.com");

            System.Console.WriteLine(html);
        }
    }
}
