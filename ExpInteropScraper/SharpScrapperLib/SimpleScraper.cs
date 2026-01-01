using System;
using System.Net;
using System.Net.Http;
using System.Threading;



namespace SharpScrapperLib
{
    public sealed class SimpleScraper : IDisposable
    {
        private HttpClient _client;

        public SimpleScraper()
        {

            try
            {
                var handler = new HttpClientHandler
                {
                    AutomaticDecompression = DecompressionMethods.GZip | DecompressionMethods.Deflate
                };

                _client = new HttpClient(handler);

                // 일부 사이트 차단 방지용 기본 헤더
                _client.DefaultRequestHeaders.UserAgent.ParseAdd("Mozilla/5.0 (compatible; SimpleScraper/1.0)");
                _client.DefaultRequestHeaders.Accept.ParseAdd("text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
            }
            catch (Exception ex)
            {
                throw;
            }

        }

        public void Dispose()
        {
            if(this._client != null)
            {
                this._client.Dispose();
                this._client = null;
            }
        }

        // HTML 문자열만 리턴 (동기)
        public string GetHtml(string url)
        {
            try
            {

                using var req = new HttpRequestMessage(HttpMethod.Get, url);
                using var resp = _client.SendAsync(req, HttpCompletionOption.ResponseHeadersRead)
                                        .GetAwaiter().GetResult();

                resp.EnsureSuccessStatusCode();

                return resp.Content.ReadAsStringAsync()
                           .GetAwaiter().GetResult();
            }
            catch (Exception ex)
            {
                throw ex;
            }

        }
    }
}
